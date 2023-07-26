#include "System.h"
#include "engine/ecs/components/CameraComponent.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/ecs/ECSContainer.h"

class CameraSystem : public System {
public:
    explicit CameraSystem(Renderer &renderer);
    
    void update();


private:
    Renderer &renderer;
};

