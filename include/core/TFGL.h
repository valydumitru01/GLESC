#include "Types.h"
#include "core/components/Component.h"
#include "core/components/TransformComponent.h"
#include "core/components/RenderComponent.h"
#include "core/components/InputComponent.h"
#include "core/components/PhysicsComponent.h"
#include "game/Game.h"
#include "core/FPS.h"

#include <vector>

class TFGL
{
private:
    std::vector<TransformComponent&>& transforms;
    std::vector<RenderComponent&>& renders;
    std::vector<InputComponent&>& inputs;
    std::vector<PhysicsComponent&>& physics;

    uint16_t numTransformComponents;
    uint16_t numRenderComponents;
    uint16_t numInputComponents;
    uint16_t numPhysicsComponents;

public:
    TFGL();
    ~TFGL();
    
    void update();
    void loop();
    ID& createEntity() const;
    std::vector<Component>* getEntityComponents(ID& entityID) const;
    void setComponentToEntity(Component& component, ID& entityID);
};

