
/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include <memory>
#include "engine/core/low-level-renderer/graphic-device-interface/concrete-gdi/opengl/OpenGLGDI.h"
#include "engine/core/low-level-renderer/graphic-device-interface/concrete-gdi/vulkan/VulkanGDI.h"
#include "GraphicInterface.h"
#include "engine/core/window/WindowManager.h"

class GDIFactory {
public:
    enum class GraphicsAPI {
        OPENGL,
        VULKAN
    };
    
    // TODO: Make graphic interface accessible from anywhere but not a static singleton
    static GraphicInterface& createInterface(GraphicsAPI api) {
        switch(api) {
            case GraphicsAPI::OPENGL:
                return OpenGLGDI();
            case GraphicsAPI::VULKAN:
                return VulkanGDI();
            default:
                throw std::invalid_argument("Invalid GraphicsAPI type");
        }
    }
};