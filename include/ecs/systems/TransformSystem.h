#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ecs/systems/System.h"
#include "ecs/components/TransformComponent.h"

class TransformSystem : System {
public:
    TransformSystem() : System("Transform System") {};
    void update();
    /**
     * @brief Calculate the model matrix for a given position, rotation, and scale
     * @details Given the position, rotation, and scale, this method calculates the model matrix
     * @param position The position vector
     * @param rotation The rotation vector
     * @param scale The scale vector
     * @return The model matrix
     */
    static glm::mat4 calculateModelMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);
    
    void init() override;
};

