#include "ecs/systems/System.h"
#include "ecs/components/CameraComponent.h"
#include "ecs/components/TransformComponent.h"

#include "core/ECSContainer.h"
#include <glm/gtc/matrix_transform.hpp>

class CameraSystem : public System {
public:
    CameraSystem() : System("Camera System"), projection(), view() {};
    
    void update();
    
    void init() override;
    
    void setRenderer(shared_ptr <Renderer> &rendererParam);

private:
    
    /**
     * @brief Creates a projection matrix from a camera component
     * @details uses the perspective function from glm
     * @param camera component
     * @return projection matrix
     */
    static glm::mat4 makeProjectionMatrix(CameraComponent &camera);
    
    /**
     * @brief Creates a view matrix from a transform component of the camera
     * @details uses the lookAt function from glm
     * @param transform component of the camera
     * @return view matrix
     */
    static glm::mat4 makeViewMatrix(TransformComponent &transform);
    
    shared_ptr <Renderer> renderer;
    
    /**
     * @brief projection matrix
     */
    glm::mat4 projection;
    /**
     * @brief view matrix
     */
    glm::mat4 view;
    
    
};

