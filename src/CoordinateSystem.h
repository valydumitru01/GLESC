#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class CoordinateSystem {
public:
    CoordinateSystem(int width, int height);
    void apply();

    int width;
    int height;

    // create transformations
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
private:

    void configModel();
    void configView();
    void configProjection();

};