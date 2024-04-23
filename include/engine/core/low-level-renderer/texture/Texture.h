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

#include "TextureStructs.h"

namespace GLESC::GAPI {
    class Texture {
    public:
        Texture() = default;
        Texture(const std::string& pathParam);
        
        ~Texture();
        
        /**
         * @brief Bind the texture to the renderer to be used in the next draw calls
         * @param slot Each renderer has a number of slots that can be used to bind textures (this
         *            depends on the platform and the renderer). This parameter specifies the slot
         *            to which the texture will be bound.
         */
        void bind(Tex::Slot slot = Tex::Slot::Slot0) const;
        
        void unbind() const;

        void load(const std::string& pathParam);

        [[nodiscard]] UInt getWidth() const { return width; }
        
        [[nodiscard]] UInt getHeight() const { return height; }
        
        [[nodiscard]] Size getTotalOfPixels() const { return width * height; }
        
        [[nodiscard]] UInt getTextureID() const { return textureID; }
        
        [[nodiscard]] Pixel getPixel(UInt x, UInt y) const;
        
        [[nodiscard]] const std::vector<UByte> &getPixelsInBytes() const{ return pixels;}
        
        [[nodiscard]] const Format &getFormat() const;
        
        [[nodiscard]] std::string toString() const;
    
    
    private:
        
        TextureID textureID{0};
        UInt width{0};
        UInt height{0};
        std::vector<UByte> pixels{};
        std::shared_ptr<Format> format;
        bool hasLoaded = false;
        
        
        void initializeData(SDL_Surface &sdlSurface);
    }; // class Texture
}