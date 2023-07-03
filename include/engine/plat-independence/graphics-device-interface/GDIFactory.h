
#include <memory>
#include "engine/plat-independence/graphics-device-interface/concrete-gdi/OpenGLGDI.h"
#include "engine/plat-independence/graphics-device-interface/concrete-gdi/VulkanGDI.h"
#include "GraphicsInterface.h"

class GDIFactory {
public:
    enum class GraphicsAPI {
        OPENGL,
        VULKAN
    };
    
    static std::unique_ptr<GraphicsInterface> createInterface(GraphicsAPI api) {
        switch(api) {
            case GraphicsAPI::OPENGL:
                return std::make_unique<OpenGLGDI>();
            case GraphicsAPI::VULKAN:
                return std::make_unique<VulkanGDI>();
            default:
                throw std::invalid_argument("Invalid GraphicsAPI type");
        }
    }
};