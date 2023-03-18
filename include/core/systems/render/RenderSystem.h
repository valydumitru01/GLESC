#pragma once
#include <iostream>
#include <unordered_map>
#include <vector> 

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/components/RenderComponent.h"
#include "CoordinateSystem.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "../Debugger.h"

class RenderSystem : public System{
public:
	explicit RenderSystem(Window& window):window(window){
        addComponentRequirement<TransformComponent>();
        addComponentRequirement<RenderComponent>();
    }
    /**
     * @brief Render the content of the screen.
     * Must be called every frame
     * 
     */
    void update(const double timeOfFrame) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto &entity: getAssociatedEntities()) {
            {
                auto &render = getComponent<RenderComponent>(entity);

                // Bind the vertex array and buffer objects
                glBindVertexArray(render.VAO);
                glCheckError();
                glBindBuffer(GL_ARRAY_BUFFER, render.VBO);
                glCheckError();

                // Set the model matrix uniform
                GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
                glUniformMatrix4fv(int(modelLoc), 1, GL_FALSE, &render.model[0][0]);

                // Draw the vertices
                glDrawArrays(GL_TRIANGLES, 0, 3);
            }

            window.swapBuffers();
        }
    }

private:
    /**
     * @brief Create a Shader Attributes object
     * 
     */
    void createShaderAttributes(){

    }
    /**
     * @brief Create VBO, VAO and EBO buffers
     * 
     */
    void createBuffers();
    /**
     * @brief Generate a texture
     * 
     * @param texture ID to the texture object
     * @param path 
     */
    void generateTexture(GLuint texture, const char* path);
    /**
     * @brief Iterate over the textures and generate them calling generateTexture()
     * 
     */
    void generateTextures();
    
    ShaderManager shaderManager;
    Window& window;
    std::unordered_map<GLuint, const char *> textures;


    std::vector<float> vertices;
    std::vector<int> indices;
    glm::mat4 trans;
    glm::mat4 trans2;
    
    unsigned int transformLoc;
    
};