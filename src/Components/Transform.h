#pragma once
#include <vector>

#include <glm/glm.hpp>
class Transform
{
public:
    Transform();
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    void move(glm::vec3 _towards, float speed);
    

    void rotate(glm::vec3 _rotation);
    void rotate(float x, float y, float z);

    void scale(glm::vec3 _scale);
    void scale(float x, float y, float z);




private:
    glm::mat4 transform;


};