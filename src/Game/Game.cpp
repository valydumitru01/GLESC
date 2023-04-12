#include "game/Game.h"

Entity camera;
Entity player;

void GLESC::init() {
    
    player.addComponent(RenderComponent());
    player.addComponent(TransformComponent());
    player.addComponent(RigidBodyComponent());
    player.addComponent(InputComponent());
    
    
    camera.addComponent(CameraComponent());
    camera.addComponent(TransformComponent());
    camera.addComponent(InputComponent());
    camera.addComponent(RenderComponent());
    camera.removeComponent<RenderComponent>();
    
}


void GLESC::loop() {
    player.getComponent <TransformComponent>().position.x += 1;
    
    player.getComponent <RenderComponent>();
}

Game::Game() {
    init();
}
