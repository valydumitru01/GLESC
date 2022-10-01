#include "Camera.h"

Camera::Camera(ShaderManager* shaderManager) {
    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	this->shaderManager=shaderManager;

	pitch=0;
	yaw = -90.0f;
	
	
}

void Camera::setDirection(float yaw, float pitch){
	

	
	
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	
	cameraFront = glm::normalize(direction);


	
}
void Camera::updateView(){
	shaderManager->setMat4("view", glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp));
}
void Camera::setElapsedTime(double deltaTime){
	this->deltaTime=deltaTime;
}
void Camera::moveUp() {
	
}

void Camera::moveDown() {
	
}

void Camera::moveRight() {
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * (float)(cameraSpeed*deltaTime);
}

void Camera::moveLeft() {
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * (float)(cameraSpeed*deltaTime);
}

void Camera::moveForward() {
	cameraPos += (float)(cameraSpeed*deltaTime) * cameraFront;
}

void Camera::moveBackwards() {
	cameraPos -= (float)(cameraSpeed*deltaTime) * cameraFront;
}

