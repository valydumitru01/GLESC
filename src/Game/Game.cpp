#include "Game.h"

Entity camera;
Entity player;

void GLESC::init() {
    player.addComponent<RenderComponent>();
    player.addComponent<TransformComponent>();
    player.addComponent<InputComponent>();

    camera.addComponent<CameraComponent>();
    camera.addComponent<TransformComponent>();
    player.removeComponent<TransformComponent>();

}


void GLESC::loop() {
    player.getComponent<TransformComponent>().position.x += 1;

    player.getComponent<RenderComponent>();
}
