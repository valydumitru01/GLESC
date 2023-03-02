#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class CameraComponent
{
public:
    void moveUp();
    void moveDown();

    void moveRight();
    void moveLeft();
    void moveForward();
    void moveBackwards();
    
    glm::mat4 getLookAtMatrix();
    void updateDirection();
    void setElapsedTime(double deltaTime);
    float cameraSpeed=2.5f;

    glm::vec3 cameraPos;
private:

    double deltaTime;
};