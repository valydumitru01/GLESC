#pragma once
#include "../Components/Transform.h"
#include "../ShaderManager.h"
#include <glm/gtc/type_ptr.hpp>
class Entity
{
public:
    Entity(ShaderManager* shaderManager);
    virtual void render(){};
    virtual void update(){};
private:
    void setTexture(int texture);
    void setTransform(glm::mat4 transform);
    Transform* transform;
    ShaderManager* shaderManager;
};