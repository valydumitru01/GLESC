#shader fragment
/* The GLSL version is automatically set */
out vec4 FragColor;

#ifdef USE_COLOR
in vec4 VertexColor;
#else
in vec2 VertexTexCoord;
#endif
in vec3 Normal;
in vec3 FragPos;

#define MAX_LIGHTS 50

struct AmbientLight {
    vec3 color;
    float intensity;
};

struct Light {
    vec3 position;
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
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(-FragPos);
    #ifdef USE_COLOR
    vec3 baseColor = VertexColor.rgb;
    #else
    vec3 baseColor = texture(Texture1, VertexTexCoord).rgb;
    #endif

    // Ambient light
    vec3 ambient = uAmbient.color * uAmbient.intensity;

    vec3 totalDiffuse = vec3(0.0);
    // Spotlights
    for (int i = 0; i < uSpotLights.count; ++i) {
        vec3 position = uSpotLights.lights[i].lightProperties.position;
        float intensity = uSpotLights.lights[i].lightProperties.intensity;
        vec3 color = uSpotLights.lights[i].lightProperties.color;

        vec3 lightDir = normalize(position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);

        vec3 diffuse = diff * color * intensity;
        totalDiffuse += diffuse;
    }



    vec3 finalColor = (ambient + totalDiffuse) * baseColor;

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
out vec3 Normal;
out vec3 FragPos;
// ==========================================


// ==========================================
// ============Uniform variables=============
// ==========================================
uniform mat4 uMVP;
uniform mat4 uModel;
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

    Normal = normal;
    FragPos = vec3(uModel * vec4(pos, 1.0));
}