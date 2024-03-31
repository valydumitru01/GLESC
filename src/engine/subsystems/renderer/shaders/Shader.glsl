#shader fragment
/* The glsl version is automatically set */
out vec4 FragColor;

#ifdef USE_COLOR
in vec4 vertexColor;
#else
in vec2 vertexTexCoord;
#endif

in vec3 Normal;
in vec3 FragPos;

// Assuming a maximum of N lights
#define MAX_LIGHTS 50
struct Light {
    vec3 position;
    vec3 color;
    float intensity;
};

uniform Light lights[MAX_LIGHTS];

uniform int numLights;// Actual number of lights to use

uniform sampler2D shadowMap;// Shadow map texture
uniform mat4 lightViewProjMatrix;// Light's view projection matrix

// Global ambient light properties (could be set via uniforms)

// Color of the global ambient light (light that scatters everywhere, makes everything visible)
// Not to be confused with sun light or global light, which is directional and casts shadows
uniform vec3 uGlobalAmbientColor;
// Intensity of the global ambient light, makes everything more or less colorful (aka less or more black)
uniform float uGlobalAmbientIntensity;// Intensity of the global ambient light

// Material properties
struct Material {
    vec3 ambientColor;
    float ambientIntensity;
    vec3 diffuseColor;
    float diffuseIntensity;
    vec3 specularColor;
    float specularIntensity;
    vec3 emissionColor;
    float emissionIntensity;
    float shininess;
};
#ifdef USE_COLOR
uniform vec4 color;
#else
uniform sampler2D texture1;
#endif

float calculateShadowFactor(vec3 fragPos, vec4 lightSpacePos) {
    // Transform fragment position to light space
    vec3 projCoords = lightSpacePos.xyz / lightSpacePos.w;
    projCoords = projCoords * 0.5 + 0.5;// Transform to [0,1] space

    // Get closest depth value from light's perspective (from shadow map)
    float closestDepth = texture(shadowMap, projCoords.xy).r;

    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    // Check whether current fragPos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;
    return shadow;
}

vec4 calculateAmbient(vec3 materialAmbientColor, vec3 globalAmbientColor, float globalAmbientIntensity,
float materialAmbientIntensity) {
    // Combine the material's ambient color with the global ambient light
    // settings and include materialAmbientIntensity in the calculation
    vec3 effectiveAmbientColor = materialAmbientColor * globalAmbientColor *
    globalAmbientIntensity * materialAmbientIntensity;
    return vec4(effectiveAmbientColor, 1.0);
}
vec4 calculateDiffuse(vec3 diffuseColor, vec3 norm, Light light, float materialDiffuseIntensity) {
    float diff = max(dot(norm, normalize(light.position - FragPos)), 0.0);
    // Multiply the result by materialDiffuseIntensity to use the uniform
    return vec4(diffuseColor * light.color.xyz, 1.0) * diff * light.intensity * materialDiffuseIntensity;
}

vec4 calculateSpecular(vec3 specularColor, vec3 norm, vec3 lightDir, vec3 viewDir, Light light,
float materialSpecularIntensity) {
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
    // Multiply the result by materialSpecularIntensity to use the uniform
    return vec4(specularColor * light.color, 1.0) * spec * materialSpecularIntensity * light.intensity;
}

vec4 calculateEmission(vec3 emissionColor, float materialEmissionIntensity) {
    return vec4(emissionColor * materialEmissionIntensity, 1.0);
}


void main() {
    // Base color
    #ifdef USE_COLOR
    vec4 baseColor = color;
    #else
    vec4 baseColor = texture(texture1, vertexTexCoord);
    #endif

    vec3 norm = Normal;// Normal is expected to be already normalized
    vec3 viewDir = normalize(-FragPos);// Assuming the camera is at the origin

    vec4 ambient = calculateAmbient(uAmbientColor, uGlobalAmbientColor, uGlobalAmbientIntensity, uAmbientIntensity);


    vec4 diffuse = vec4(0.0);
    vec4 specular = vec4(0.0);
    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(lights[i].position - FragPos);
        // Calculate shadow factor for the current light
        float shadowFactor = calculateShadowFactor(FragPos, lightViewProjMatrix * vec4(FragPos, 1.0));
        // Dimming factor for shadows
        float shadowDimming = 1.0 - shadowFactor;// Assuming shadowFactor is 1.0 if in shadow, 0.0 if not

        // Adjust diffuse and specular contributions based on shadow
        vec4 currentDiffuse = calculateDiffuse(uDiffuseColor, norm, lights[i], uDiffuseIntensity) * shadowDimming;
        vec4 currentSpecular = calculateSpecular(uSpecularColor, norm, lightDir, viewDir, lights[i], uSpecularIntensity)
        * shadowDimming;


        diffuse += currentDiffuse * baseColor;
        specular += currentSpecular;
    }

    vec4 emission = calculateEmission(uEmissionColor, uEmissionIntensity) ;

    // The final color includes ambient, diffuse, and specular components
    vec4 color = ambient + diffuse + specular + emission;

    FragColor = color;
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
out vec4 vertexColor;
#else
out vec2 vertexTexCoord;
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
    vertexColor = color;// Pass the color to the fragment shader.
    #else
    vertexTexCoord = texCoord;// Pass the texture coordinate to the fragment shader.
    #endif

    Normal = normal;
    FragPos = vec3(transformedPosition.xyz);
}