#shader fragment
/* The GLSL version is automatically set */
out vec4 FragColor;

#ifdef USE_COLOR
in vec4 VertexColor;
#else
in vec2 VertexTexCoord;
#endif
in vec3 NormalViewSpace;
in vec3 FragPosViewSpace;

#define MAX_LIGHTS 50

struct AmbientLight {
    vec3 color;
    float intensity;
};

struct Light {
    vec3 posInViewSpace;
    vec3 color;
    float intensity;
};

struct GlobalSun {
    Light lightProperties;
    vec3 direction;
    sampler2D shadowMap;
    mat4 viewProjMatrix;
};

struct LightSpot {
    Light lightProperties;
    float radius;
};

struct SpotLights {
    LightSpot lights[MAX_LIGHTS];
    int count;// Actual number of lights to use
};

struct Material {
    float diffuseIntensity;
    vec3 specularColor;
    float specularIntensity;
    vec3 emissionColor;
    float emissionIntensity;
    float shininess;
};

uniform GlobalSun uGlobalSunLight;
uniform AmbientLight uAmbient;
uniform SpotLights uSpotLights;
uniform Material uMaterial;

#ifdef USE_COLOR
uniform vec4 Color;
#else
uniform sampler2D Texture1;
#endif


struct LightContribution {
    vec3 diffuse;
    vec3 specular;
};


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
    // Spotlights
    for (int i = 0; i < uSpotLights.count; ++i) {
        vec3 lightPosViewSpace = uSpotLights.lights[i].lightProperties.posInViewSpace;
        float intensity = uSpotLights.lights[i].lightProperties.intensity;
        vec3 color = uSpotLights.lights[i].lightProperties.color;

        // Diffuse
        vec3 lightDir = normalize(lightPosViewSpace - FragPosViewSpace);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * color * intensity;
        totalDiffuse += diffuse;

        // Specular
        float materialShininessMapped = uMaterial.shininess * 256.0;
        vec3 reflectDir = reflect(lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininessMapped);
        vec3 specular = uMaterial.specularIntensity * spec * uMaterial.specularColor * intensity;
        totalSpecular += specular;
    }



    vec3 finalColor = (ambient + totalDiffuse + totalSpecular) * baseColor;

    FragColor = vec4(finalColor, 1.0);
}


#shader vertex
/* The glsl version is automatically set */
// ==========================================
// ============Vertex attributes=============
// ==========================================
layout (location = 0) in vec3 pos;
#ifdef USE_COLOR
layout (location = 1) in vec4 color;
#else
layout (location = 1) in vec2 texCoord;
#endif
layout (location = 2) in vec3 normal;
//#ifdef USE_INSTANCING
//layout (location = 3) in vec3 instancePos;
//#endif
// ==========================================


// ==========================================
// ============Output variables==============
// ==========================================
#ifdef USE_COLOR
out vec4 VertexColor;
#else
out vec2 VertexTexCoord;
#endif
out vec3 NormalViewSpace;
out vec3 FragPosViewSpace;
// ==========================================


// ==========================================
// ============Uniform variables=============
// ==========================================
uniform mat4 uMVP;
uniform mat4 uMV;
uniform mat3 uNormalMat;
// ==========================================

void main() {
    vec4 transformedPosition;

    #ifdef USE_INSTANCING
    transformedPosition = uMVP * vec4(pos + instancePos, 1.0);
    #else
    transformedPosition = uMVP * vec4(pos, 1.0);
    #endif

    gl_Position = transformedPosition;

    #ifdef USE_COLOR
    VertexColor = color;// Pass the color to the fragment shader.
    #else
    VertexTexCoord = texCoord;// Pass the texture coordinate to the fragment shader.
    #endif

    NormalViewSpace = uNormalMat * normal;
    FragPosViewSpace = vec3(uMV * vec4(pos, 1.0));
}