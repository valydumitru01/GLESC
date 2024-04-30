
//██████████████████████████████████████████
//██████    ██     █████  ██████   █████████
//██████ █████ ███ ███ ███ ███ █████████████
//██████   ███    ████     ███ ██  █████████
//██████ █████ ██ ████ ███ ███ ████ ████████
//██████ █████ ███ ███ ███ █████   █████████
//██████████████████████████████████████████
#shader fragment
/* The GLSL version is automatically set */

// ==========================================
// ------------ Output variables ------------
// ------------------------------------------
// The output of the fragment shader (the color of the pixel).
// It is stored in the variable FragColor.
out vec4 FragColor;
// ==========================================




// ==========================================
// ------------- Input variables ------------
// ------------------------------------------
#ifdef USE_COLOR
in vec4 VertexColor;
#else
in vec2 VertexTexCoord;
#endif
in vec3 NormalViewSpace;
in vec3 FragPosViewSpace;
// ==========================================




// ==========================================
// --------------- Light Data ---------------
// ------------------------------------------
#define MAX_LIGHTS 50
#define MAX_SUNS 10

struct AmbientLight {
    vec3 color;
    float intensity;
};

struct GlobalSun {
    vec3 color;
    float intensity;
    vec3 direction;
    sampler2D shadowMap;
    mat4 viewProjMatrix;
};

struct GlobalSuns {
    vec3 color[MAX_SUNS];
    float intensity[MAX_SUNS];
    vec3 direction[MAX_SUNS];
    uint count;
};

struct LightSpots {
    vec3 posInViewSpace[MAX_LIGHTS];
    vec3 color[MAX_LIGHTS];
    float intensity[MAX_LIGHTS];
    float radius[MAX_LIGHTS];
    uint count;
};

struct LightContribution {
    vec3 diffuse;
    vec3 specular;
};
// ==========================================




// ==========================================
// ------------ Material Data ---------------
// ------------------------------------------
struct Material {
    float diffuseIntensity;
    vec3 specularColor;
    float specularIntensity;
    vec3 emissionColor;
    float emissionIntensity;
    float shininess;
};
// ==========================================




// ==========================================
// ---------------- Unforms -----------------
// ------------------------------------------
uniform GlobalSuns uGlobalSuns;
uniform AmbientLight uAmbient;
uniform LightSpots uLights;
uniform Material uMaterial;
#ifdef USE_COLOR
uniform vec4 Color;
#else
uniform sampler2D Texture1;
#endif
// ==========================================



void main() {
    vec3 viewDir = normalize(-FragPosViewSpace);
    vec3 norm = normalize(NormalViewSpace);
    #ifdef USE_COLOR
    vec3 baseColor = VertexColor.rgb;
    #else
    vec3 baseColor = texture(Texture1, VertexTexCoord).rgb;
    #endif
    // Ambient light
    vec3 ambient = uAmbient.color * uAmbient.intensity;

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    for (uint i = 0; i < uGlobalSuns.count; ++i) {
        vec3 sunDir = -uGlobalSuns.direction[i];
        float sunIntensity = uGlobalSuns.intensity[i];
        vec3 sunColor = uGlobalSuns.color[i];

        // Diffuse
        float diff = max(dot(norm, sunDir), 0.0);
        vec3 diffuse = diff * sunColor * sunIntensity;

        totalDiffuse += diffuse;

        // Specular
        float materialShininessMapped = uMaterial.shininess * 256.0;
        vec3 reflectDir = reflect(-sunDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininessMapped);
        vec3 specular = uMaterial.specularIntensity * spec * uMaterial.specularColor * sunIntensity;
        totalSpecular += specular;
    }

    for (uint i = 0; i < uLights.count; ++i) {
        vec3 lightPosViewSpace =  uLights.posInViewSpace[i];
        float intensity = uLights.intensity[i];
        vec3 color = uLights.color[i];
        float radius = uLights.radius[i];

        vec3 fragmentLightVec = lightPosViewSpace - FragPosViewSpace;
        float distanceToFrag = length(fragmentLightVec);

        // Skip if distance is greater than the radius of the light.
        if (distanceToFrag > uLights.radius[i]) continue;

        // Formula obtained from
        // https://gamedev.stackexchange.com/questions/56897/glsl-light-attenuation-color-and-intensity-formula
        float minLight = 0.01;
        float a = 0.1;
        float b = 1.0 / (radius*radius * minLight);
        float att = 1.0 / (1.0 + a*distanceToFrag + b*distanceToFrag*distanceToFrag);


        // Diffuse
        vec3 lightDir = normalize(fragmentLightVec);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * color * intensity * att;

        totalDiffuse += diffuse;

        // Specular
        float materialShininessMapped = uMaterial.shininess * 256.0;
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininessMapped);
        vec3 specular = uMaterial.specularIntensity * spec * uMaterial.specularColor * intensity;
        totalSpecular += specular;
    }

    vec3 finalColor = (ambient + totalDiffuse + totalSpecular) * baseColor;

    FragColor = vec4(finalColor, 1.0);
}





//██████████████████████████████████████████
//█████ ██████ ███     ███     ███     █████
//█████ ██████ ███ ███████ ███ █████ ███████
//█████ ██████ ███    ████   ███████ ███████
//███████ ██ █████ ███████ ██ ██████ ███████
//█████████ ██████     ███ ███ █████ ███████
//██████████████████████████████████████████
#shader vertex
/* The glsl version is automatically set */
// ==========================================
// ----------- Vertex attributes ------------
// ------------------------------------------
layout (location = 0) in vec3 aPos;
#ifdef USE_COLOR
layout (location = 1) in vec4 aColor;
#else
layout (location = 1) in vec2 aTexCoord;
#endif
layout (location = 2) in vec3 aNormal;
//#ifdef USE_INSTANCING
//layout (location = 3) in vec3 instancePos;
//#endif
// ==========================================


// ==========================================
// ------------ Output variables ------------
// ------------------------------------------
#ifdef USE_COLOR
out vec4 VertexColor;
#else
out vec2 VertexTexCoord;
#endif
out vec3 NormalViewSpace;
out vec3 FragPosViewSpace;
// ==========================================


// ==========================================
// ------------ Uniform variables -----------
// ------------------------------------------
uniform mat4 uMVP;
uniform mat4 uMV;
uniform mat3 uNormalMat;
// ==========================================

void main() {
    vec4 transformedPosition;

    #ifdef USE_INSTANCING
    transformedPosition = uMVP * vec4(aPos + instancePos, 1.0);
    #else
    transformedPosition = uMVP * vec4(aPos, 1.0);
    #endif

    gl_Position = transformedPosition;

    #ifdef USE_COLOR
    VertexColor = aColor;// Pass the color to the fragment shader.
    #else
    VertexTexCoord = aTexCoord; // Pass the texture coordinate to the fragment shader.
    #endif
    NormalViewSpace = uNormalMat * aNormal;
    FragPosViewSpace = vec3(uMV * vec4(aPos, 1.0));
}