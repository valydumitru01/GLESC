#include "ecs/systems/RenderSystem.h"

RenderSystem::RenderSystem(shared_ptr <WindowManager> windowManager) : windowManager(windowManager) {
    addComponentRequirement <TransformComponent>();
    addComponentRequirement <RenderComponent>();
    
    
}

void RenderSystem:update(const double timeOfFrame) {
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (auto &entity: getAssociatedEntities()) {
        {
            auto &render = getComponent <RenderComponent>(entity);
            auto &transform = getComponent <TransformComponent>(entity);
            
            // Bind the vertex array and buffer objects
            
            
            auto &model = render.model;
            model = glm::translate(model, transform.position);
            model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, transform.scale);
            
            
            // Set the view matrix uniform
            GLuint viewLoc = glGetUniformLocation(shaderManager.getShaderProgram(), "view");
            glUniformMatrix4fv(int(viewLoc), 1, GL_FALSE, &render.view[0][0]);
            glCheckError();
            
            
            // Set the projection matrix uniform
            renderer->getShaderManager()->getShaderProgram()->
            GLuint projectionLoc = glGetUniformLocation(, "projection");
            glUniformMatrix4fv(int(projectionLoc), 1, GL_FALSE, &render.projection[0][0]);
            glCheckError();
            
            // Set the texture uniform
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, render.texture);
            glCheckError();
            GLuint textureLoc = glGetUniformLocation(shaderManager.getShaderProgram(), "texture1");
            glUniform1i(textureLoc, 0);
            glCheckError();
            // Draw the vertices
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        // TODO: Batch rendering
        windowManager.get()->swapBuffers();
    }
}