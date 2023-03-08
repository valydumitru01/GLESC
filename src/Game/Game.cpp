#include "Game.h"
Entity camera;
Entity player;

void TFGL::init(){
	player.addComponent<RenderComponent>();
	player.addComponent<TransformComponent>();
	player.addComponent<InputComponent>();
	
	camera.addComponent<CameraComponent>();
	camera.addComponent<TransformComponent>();
	player.removeComponent<TransformComponent>();
	
}


void TFGL::loop(){
	player.getComponent<TransformComponent>().position.x+=1;
	
	player.getComponent<RenderComponent>();
}
