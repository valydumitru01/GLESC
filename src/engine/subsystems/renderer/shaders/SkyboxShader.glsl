#shader fragment
/* The glsl version is automatically set */
layout (location = 0) in vec3 aPosition;

out vec3 TexCoords;

uniform mat4 vp; // View projection matrix

void main() {
    TexCoords = aPosition;
    vec4 pos = vp * vec4(aPosition, 1.0);
    gl_Position = pos.xyww; // Keep depth as w to ensure it's rendered as a background
}


#shader fragment
/* The glsl version is automatically set */
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main() {
    FragColor = texture(skybox, TexCoords);
}