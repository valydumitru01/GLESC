#include "System.h"
#include "engine/ecs/ECSContainer.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/ecs/components/RigidBodyComponent.h"

class PhysicsSystem : public System {
private:
    glm::vec3 gravity;

public:
    PhysicsSystem() : System("Physics System"), gravity({0,8.91,0}) {};
    void update();
    
    void init() override;
    
};

