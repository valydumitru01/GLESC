
#include <memory>
#include "engine/core/graphics-device-interface/concrete-gdi/opengl/OpenGLGDI.h"
#include "engine/core/graphics-device-interface/concrete-gdi/vulkan/VulkanGDI.h"
#include "GraphicsInterface.h"

class GDIFactory {
public:
    enum class GraphicsAPI {
        OPENGL,
        VULKAN
    };
    
    static GraphicsInterface& createInterface(GraphicsAPI api, WindowManager &window) {
        switch(api) {
            case GraphicsAPI::OPENGL:
                return OpenGLGDI(window);
            case GraphicsAPI::VULKAN:
                return VulkanGDI(window);
            default:
                throw std::invalid_argument("Invalid GraphicsAPI type");
        }
    }
};