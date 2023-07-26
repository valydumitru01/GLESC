#include "game/Game.h"


void Engine::initGame() {
    // TODO: Create a game class
    createEntity("player");
    createEntity("camera");
    getEntity("player")
        .addComponent(RenderComponent())
        .addComponent(TransformComponent())
        .addComponent(RigidBodyComponent())
        .addComponent(InputComponent());
    
    // Prepare the vertex data for the triangle
    std::vector <float> vertices = {-0.5f, -0.5f, 0.0f, // Bottom left
                                    0.5f, -0.5f, 0.0f, // Bottom right
                                    0.0f, 0.5f, 0.0f  // Top
    };
    
    // Prepare the index data for the triangle
    std::vector <unsigned int> indices = {0, 1, 2};
    
    // Prepare the vertex attributes for the triangle
    std::vector <VertexAttribute> vertexAttributes = {{0, 3, 0} // location = 0, size = 3, offset = 0
    };
    
    // Create the mesh and initialize it with the prepared data
    Mesh triangleMesh;
    triangleMesh.create(vertices, indices, vertexAttributes);
    
    getEntity("player").getComponent <RenderComponent>().mesh = triangleMesh;
    
    getEntity("camera")
        .addComponent(CameraComponent())
        .addComponent(TransformComponent())
        .addComponent(InputComponent())
        .addComponent(RenderComponent())
        .removeComponent <RenderComponent>();
}


void Engine::loop() {
    getEntity("player").getComponent <RigidBodyComponent>().velocity.x = 1;
    
    getEntity("player").getComponent <RenderComponent>();
}

Game::Game() {
    initGame();
}
