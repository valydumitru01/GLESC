#include "renderer/CoordinateSystem.h"

CoordinateSystem::CoordinateSystem(int width, int height, glm::vec3 initialCameraPos) {

    //Initiate each matrix
    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    //Initial position of the view
    view = glm::translate(view, initialCameraPos);

    setProjection(width, height);
    //Matrix need initialization to identity matrix
}

void CoordinateSystem::setModel() {
    model = glm::mat4(1.0f);
    //model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
}

void CoordinateSystem::setView(glm::mat4 cameraLookAtMat4) {
    view = cameraLookAtMat4;
}

void CoordinateSystem::setProjection(int width, int height) {
    projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float) height / (float) width, 0.1f, 100.0f);
}

