#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class CoordinateSystem {
public:
    /**
     * How our coordinates system looks like
     * Remember OpenGL works with right-handed coordinates (Positive X-Axis is to the right)
     *             +Y    -Z
     *              |   /
     *              |
     *              | /
     * -X _ _ _ _ _ |______________ +X
     *             /
     *            / |
     *           /
     *          /   |
     *       +Z    -Y
     */
    CoordinateSystem(int width, int height, glm::vec3 initialCameraPos);


    // create transformations
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    void setModel();

    void setView(glm::mat4 cameraLookAtMat4);

    void setProjection(int width, int height);

private:


};