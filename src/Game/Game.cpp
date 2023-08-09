/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/GLESC.h"
#include "engine/ecs/frontend/entity/Entity.h"

// Components
#include "engine/ecs/backend/component/components/RenderComponent.h"
#include "engine/ecs/backend/component/components/CameraComponent.h"
#include "engine/ecs/backend/component/components/PhysicsComponent.h"
#include "engine/ecs/backend/component/components/TransformComponent.h"
#include "engine/ecs/backend/component/components/InputComponent.h"



void GLESC::Engine::initGame() {
    // TODO: Create a game class
    Entity player = createEntity("player");
    Entity camera = createEntity("camera");
    player.addComponent(RenderComponent())
          .addComponent(TransformComponent())
          .addComponent(RigidBodyComponent())
          .addComponent(InputComponent());
    
    camera.addComponent(CameraComponent())
          .addComponent(TransformComponent())
          .addComponent(InputComponent())
          .addComponent(RenderComponent())
          .removeComponent<RenderComponent>();
    
    // Prepare the vertex data for the triangle
    std::vector<float> vertices = {-0.5f, -0.5f, 0.0f, // Bottom left
                                   0.5f, -0.5f, 0.0f, // Bottom right
                                   0.0f, 0.5f, 0.0f  // Top
    };
    std::vector<float> uvs = {0.0f, 0.0f, // Bottom left
                              1.0f, 0.0f, // Bottom right
                              0.5f, 1.0f  // Top
    };
    
    
    // Create the mesh and initialize it with the prepared data
    GLESC::Mesh mesh;
    GLESC::VertexIndex vertexIndex1 = mesh.addVertex({vertices[0], vertices[1], vertices[2], uvs[0], uvs[1]});
    GLESC::VertexIndex vertexIndex2 = mesh.addVertex({vertices[3], vertices[4], vertices[5], uvs[2], uvs[3]});
    GLESC::VertexIndex vertexIndex3 = mesh.addVertex({vertices[6], vertices[7], vertices[8], uvs[4], uvs[5]});
    
    mesh.addFace(vertexIndex1, vertexIndex2, vertexIndex3);
    
    player.getComponent<RenderComponent>().mesh = mesh;
    
    
    
    player.getComponent<RigidBodyComponent>().velocity.x = 1;
    
    
}


void GLESC::Engine::loop() {


}