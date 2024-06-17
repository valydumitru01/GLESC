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
in vec3 SunDirViewSpace;
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
    sampler2D shadowMap;
    mat4 viewProjMatrix;
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
// ---------------- Fog Data ----------------
// ------------------------------------------

struct Fog {
    float density;
    float end;
    vec3 color;
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
uniform Fog uFog;
uniform AmbientLight uAmbient;
uniform LightSpots uLights;
uniform Material uMaterial;
uniform GlobalSun uGlobalSun;
#ifdef USE_COLOR
uniform vec4 Color;
#else
uniform sampler2D Texture1;
#endif
// ==========================================

float calculateAttenuation(float distance, float radius) {
    // Formula obtained from
    // https://gamedev.stackexchange.com/questions/56897/glsl-light-attenuation-color-and-intensity-formula
    float minLight = 0.01f;
    float a = 0.1;
    float b = 1.0f / (radius*radius * minLight);
    return 1.0f / (1.0f + a*distance + b*distance*distance);
}

vec3 calculateSpecular(vec3 lightDir, vec3 norm, vec3 viewDir, float shininess,
vec3 specularColor, float materialSpecularIntensity, float att, float intensity) {
    if (shininess < 0.01) {
        return vec3(0.0);// No specular highlight if shininess is close to zero
    }
    float materialShininessMapped = shininess * 256.0f;
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininessMapped);
    return intensity * spec * specularColor * materialSpecularIntensity;
}

vec3 calculateDiffuse(vec3 lightDir, vec3 norm, vec3 color, float intensity, float att) {
    float diff = max(dot(norm, lightDir), 0.0);
    return diff * color * intensity * att;
}

float calculateFogFactor(float distanceToPixel, float fogEnd, float density) {
    float distRatio = 4.0f * distanceToPixel / fogEnd;
    float fogFactor = exp(-distRatio * density * distRatio * density);
    return fogFactor;
}

void main() {
    vec3 viewDir = normalize(-FragPosViewSpace);
    vec3 norm = NormalViewSpace;
    #ifdef USE_COLOR
    vec3 baseColor = VertexColor.rgb;
    #else
    vec3 baseColor = texture(Texture1, VertexTexCoord).rgb;
    #endif
    // Ambient light
    vec3 ambient = uAmbient.color * uAmbient.intensity;

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    // Applying the sun light
    vec3 sunDir = -SunDirViewSpace;
    float sunIntensity = uGlobalSun.intensity;
    vec3 sunColor = uGlobalSun.color;

    // Diffuse
    totalDiffuse += calculateDiffuse(sunDir, norm, sunColor, sunIntensity, 1.0);

    // Specular
    totalSpecular += 0.1 * calculateSpecular(sunDir, norm, viewDir, uMaterial.shininess,
    uMaterial.specularColor, uMaterial.specularIntensity, 1.0, sunIntensity);


    for (uint i = 0; i < uLights.count; ++i) {
        vec3 lightPosViewSpace =  uLights.posInViewSpace[i];
        float intensity = uLights.intensity[i];
        vec3 color = uLights.color[i];
        float radius = uLights.radius[i];

        vec3 lightDir = lightPosViewSpace - FragPosViewSpace;
        float distanceToFrag = length(lightDir);
        // Skip if distance is greater than the radius of the light.
        if (distanceToFrag > uLights.radius[i]) continue;

        vec3 lightDirNormalized = normalize(lightDir);

        float att = calculateAttenuation(distanceToFrag, radius);

        // Diffuse
        totalDiffuse += calculateDiffuse(lightDirNormalized, norm, color, intensity, att);

        // Specular
        totalSpecular += calculateSpecular(lightDirNormalized, norm, viewDir, uMaterial.shininess,
        uMaterial.specularColor, uMaterial.specularIntensity, att, intensity);


    }

    vec3 finalColor = (ambient + totalDiffuse + totalSpecular) * baseColor;

    float fogFactor = calculateFogFactor(length(FragPosViewSpace), uFog.end, uFog.density);
    vec3 foggedColor = mix(uFog.color, finalColor, fogFactor);

    FragColor = vec4(foggedColor, 1.0);
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
layout (location = 1) in vec3 aNormal;
#ifdef USE_COLOR
layout (location = 2) in vec4 aColor;
#else
layout (location = 2) in vec2 aTexCoord;
#endif
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
out vec3 SunDirViewSpace;
// ==========================================


// ==========================================
// ------------ Uniform variables -----------
// ------------------------------------------
uniform mat4 uMVP;
uniform mat4 uMV;
uniform mat3 uNormalMat;
uniform vec3 uSunDirection;
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
    VertexTexCoord = aTexCoord;// Pass the texture coordinate to the fragment shader.
    #endif
    NormalViewSpace = normalize(uNormalMat * aNormal);
    FragPosViewSpace = vec3(uMV * vec4(aPos, 1.0));

    // Transform sun direction to view space using the normal matrix
    SunDirViewSpace = normalize(uNormalMat * uSunDirection);
}