#include "ecs/systems/System.h"
#include "core/ECSContainer.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/components/RigidBodyComponent.h"

class PhysicsSystem : public System {
private:
    double gravity{9.81F};

public:
    PhysicsSystem() : System("Physics System") {};
    void update();
    
    void init() override;
    
};

