#include "core/systems/System.h"
#include "core/components/CameraComponent.h"
#include "core/ECSContainer.h"

class CameraSystem : public System {
public:
    void update() {
        for (auto &entity: getAssociatedEntities()) {
            mvp = MakeProjectionTransform(&getComponent<CameraComponent>(entity));
        }
    }

    glm::mat4 &getMvp() { return mvp; };
private:
    glm::mat4 mvp;

    static glm::mat4
    MakeProjectionTransform(CameraComponent *camera) {
        float zClipBias0 = (camera->farPlane + camera->nearPlane) / (camera->farPlane - camera->nearPlane);

        float zClipBias1 = (2.0f * camera->farPlane * camera->nearPlane) / (camera->farPlane - camera->nearPlane);

        float zoomX = 1.0f / tanf((camera->fov / 2.0f) * (M_PI / 180.0f));
        float zoomY = (zoomX * static_cast<float>(camera->viewWidth)) / static_cast<float>(camera->viewHeight);

        glm::mat4 transform;
        transform[0][0] = zoomX;
        transform[1][1] = zoomY;
        transform[2][2] = -zClipBias0;
        transform[3][2] = -1;
        transform[2][3] = -zClipBias1;

        return transform;
    }
};

