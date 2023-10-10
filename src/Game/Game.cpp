/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/GLESC.h"
#include "engine/ecs/frontend/entity/Entity.h"

// Components
#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/CameraComponent.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/ecs/frontend/component/InputComponent.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"


void GLESC::Engine::initGame() {
    // TODO: Create a game class
    Entity player = createEntity("player");
    Entity camera = createEntity("camera");
    player.addComponent(RenderComponent())
            .addComponent(TransformComponent())
            .addComponent(PhysicsComponent())
            .addComponent(InputComponent());
    
    camera.addComponent(CameraComponent())
            .addComponent(TransformComponent())
            .addComponent(InputComponent())
            .addComponent(RenderComponent())
            .removeComponent<RenderComponent>();
    
    
    
    player.getComponent<RenderComponent>().mesh = MeshFactory::cube(10);
    
    
    player.getComponent<PhysicsComponent>().velocity.z(1);
    
    
}


void GLESC::Engine::loop() {


}