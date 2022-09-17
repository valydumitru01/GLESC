#include "CoordinateSystem.h"

CoordinateSystem::CoordinateSystem(int width, int height)
{
    this->width=width;
    this->height=height;
    //Matrix need initialization to identity matrix
}
void CoordinateSystem::configModel()
{
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}
void CoordinateSystem::configView()
{
    view = glm::mat4(1.0f);
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
}
void CoordinateSystem::configProjection()
{
    projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)1200 / (float)1000, 0.1f, 100.0f);
}

void CoordinateSystem::apply()
{

    //Reconfigure each matrix
    configModel();
    configView();
    configProjection();
}
