#include "System.h"
#include "engine/ecs/components/CameraComponent.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/ecs/ECSContainer.h"

class CameraSystem : public System {
public:
    CameraSystem() : System("Camera System") {};
    
    void update();
    
    void init() override;
    


private:
    Renderer& renderer;
};

