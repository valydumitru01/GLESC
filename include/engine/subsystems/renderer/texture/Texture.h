/**************************************************************************************************
 * @file   Texture.h
 * @author Valentin Dumitru
 * @date   27/11/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/res-mng/textures/TextureSurface.h"

namespace GLESC::Render {
    class Texture {
    public:
        Texture() = default;
        explicit Texture(const std::string& path, bool flipTexture = true);
        
        ~Texture();
        
        /**
         * @brief Bind the texture to the renderer to be used in the next draw calls
         * @param textureSlot Each renderer has a number of slots that can be used to bind textures (this
         *            depends on the platform and the renderer). This parameter specifies the slot
         *            to which the texture will be bound.
         */
        void bind(TextureSlot textureSlot = 0) const;
        
        void unbind() const;

        void load(const std::string& path, bool flipTexture);
        void release();
        
        [[nodiscard]] UInt getTextureID() const { return textureID; }

        [[nodiscard]] bool hasBeenLoaded() const { return hasLoaded; }

        [[nodiscard]] const ResMng::Texture::TextureSurface& getTextureSurface() const { return textureSurface; }
    
    
    private:

        void load(const ResMng::Texture::TextureSurface& textureSurfaceParam);
        bool hasLoaded{false};
        TextureID textureID{0};
        ResMng::Texture::TextureSurface textureSurface;

    }; // class Texture
}
