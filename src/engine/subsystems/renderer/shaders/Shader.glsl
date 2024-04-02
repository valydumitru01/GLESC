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

// Assuming a maximum of N lights
#define MAX_LIGHTS 50

struct GlobalAmbientLight {
    vec3 color;
    float intensity;
};

struct LightContribution {
    vec3 Diffuse;
    vec3 Specular;
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

struct LightSpots {
    LightSpot lights[MAX_LIGHTS];
    int size; // Actual number of lights to use
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
uniform GlobalAmbientLight uGlobalAmbient;
uniform LightSpots uSpotLights;
uniform Material uMaterial;

#ifdef USE_COLOR
uniform vec4 Color;
#else
uniform sampler2D Texture1;
#endif

float calculateShadowFactor(GlobalSun sun, vec3 fragPos) {
    vec4 lightSpacePos = sun.viewProjMatrix * vec4(fragPos, 1.0);
    vec3 projCoords = lightSpacePos.xyz / lightSpacePos.w;
    projCoords = projCoords * 0.5 + 0.5; // Transform to [0,1] space

    float closestDepth = texture(sun.shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    float shadow = currentDepth > closestDepth ? 1.0 : 0.0;
    return shadow;
}

vec3 calculateAmbient(GlobalAmbientLight globalAmbient, vec3 baseColor) {
    return baseColor * globalAmbient.color * globalAmbient.intensity;
}

LightContribution calculateLightContribution(vec3 fragPos, vec3 norm, vec3 viewDir, Light light) {
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color * light.intensity;

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = spec * light.color * uMaterial.specularIntensity;

    return LightContribution(diffuse, specular);
}

void main() {
    #ifdef USE_COLOR
    vec3 baseColor = VertexColor.rgb;
    #else
    vec3 baseColor = texture(Texture1, VertexTexCoord).rgb;
    #endif

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(-FragPos);
    vec3 ambientColor = calculateAmbient(uGlobalAmbient, baseColor);

    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    for (int i = 0; i < uSpotLights.size; ++i) {
        LightContribution contribution = calculateLightContribution(FragPos, norm, viewDir, uSpotLights.lights[i].lightProperties);
        diffuse += contribution.Diffuse * uMaterial.diffuseIntensity;
        specular += contribution.Specular;
    }

    // Calculate contribution from the global sun light
    float shadowFactor = calculateShadowFactor(uGlobalSunLight, FragPos);
    float shadowDimming = 1.0 - shadowFactor;
    LightContribution sunContribution = calculateLightContribution(FragPos, norm, viewDir, uGlobalSunLight.lightProperties);
    diffuse += sunContribution.Diffuse * shadowDimming * uMaterial.diffuseIntensity;
    specular += sunContribution.Specular * shadowDimming;

    vec3 emission = uMaterial.emissionColor * uMaterial.emissionIntensity;

    vec3 finalColor = ambientColor + diffuse + specular + emission;
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
    FragPos = vec3(transformedPosition.xyz);
}