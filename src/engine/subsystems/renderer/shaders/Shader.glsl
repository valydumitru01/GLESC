#shader fragment
/* The glsl version is automatically set */
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
    FragColor = vec4(color, 1.0);
}

#shader vertex
/* The glsl version is automatically set */
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 outColor;
out vec2 outTexCoord;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(pos, 1.0f);

    outColor = color;
    outTexCoord = vec2(texCoord.x, texCoord.y);
}