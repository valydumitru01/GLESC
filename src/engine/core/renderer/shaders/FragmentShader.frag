/* Version of OpenGL */
#version 430 core

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