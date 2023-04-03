#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

#include "GL/glew.h"
#include "GL/glu.h"
#include "GL/gl.h"

#include "SDL2/SDL.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ecs/components/RenderComponent.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/systems/System.h"

#include "renderer/Renderer.h"


class RenderSystem : public System {
public:
    explicit RenderSystem(shared_ptr <WindowManager> windowManager);
    
    ~RenderSystem();
    
    /**
     * @brief Render the content of the screen.
     * Must be called every frame
     *
     */
    void update(const double timeOfFrame);


private:
    std::shared_ptr <WindowManager> windowManager;
    std::shared_ptr <Renderer> renderer;
};