#pragma once
#include "ShaderManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
    Camera(ShaderManager* shaderManager);
    void moveUp();
    void moveDown();

    void moveRight();
    void moveLeft();
    void moveForward();
    void moveBackwards();
    
    void updateView();
    void setDirection(float yaw, float pitch);
    void setElapsedTime(double deltaTime);
    float cameraSpeed=2.5f;
    float pitch;
    float yaw;

private:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    double deltaTime;
    ShaderManager* shaderManager;
};