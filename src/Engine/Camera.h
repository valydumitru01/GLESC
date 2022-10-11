#pragma once
#include "Renderer/ShaderManager.h"
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
    
    glm::mat4 getLookAtMatrix();
    void updateDirection();
    void setElapsedTime(double deltaTime);
    float cameraSpeed=2.5f;
    float pitch;
    float yaw;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
private:

    double deltaTime;
    ShaderManager* shaderManager;
};