#include <glm/glm.hpp>
#include <gl.h>

class MaterialComponent {
public:
    GLuint diffuseTexture;
    GLuint specularTexture;
    GLuint normalTexture;
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
    float shininess;
};