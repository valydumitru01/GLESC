
#include "core/entities/Entity.h"
Entity::Entity(ShaderManager* shaderManager){
    this->shaderManager=shaderManager;
}
void Entity::setTexture(int texture) {
	
}

void Entity::setTransform(glm::mat4 transform) {

    glUniformMatrix4fv(glGetUniformLocation(shaderManager->getShaderProgramID(), "transform"), 1, GL_FALSE, glm::value_ptr(transform));
}
