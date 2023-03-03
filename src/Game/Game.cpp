#include "Game.h"
void TFGL::init(){
	Entity player;
	player.addComponent(RenderComponent());
	player.addComponent(TransformSystem());
	player.addComponent(InputComponent());
	Entity camera;
	camera.addComponent( CameraComponent());
	camera.addComponent( TransformComponent());
}


void TFGL::loop(){

}
