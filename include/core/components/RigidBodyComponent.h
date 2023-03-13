#include "glm/glm.hpp"
class RigidBodyComponent{
public:
    float mass;
    glm::vec3 velocity;
    glm::vec3 force;

    explicit RigidBodyComponent(float m = 1.0F) : mass(m), velocity(0.0F), force(0.0F) {}
};