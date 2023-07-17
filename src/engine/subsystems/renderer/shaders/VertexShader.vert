/* Version for OpenGL */
#version 430 core
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