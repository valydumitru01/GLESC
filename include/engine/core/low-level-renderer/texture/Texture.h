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

#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"
#include "TextureStructs.h"

namespace GLESC {
    class Texture {
    public:
        Texture(std::string pathParam);
        
        ~Texture();
        
        /**
         * @brief Bind the texture to the renderer to be used in the next draw calls
         * @param slot Each renderer has a number of slots that can be used to bind textures (this
         *            depends on the platform and the renderer). This parameter specifies the slot
         *            to which the texture will be bound.
         */
        void bind(Tex::Slot slot = Tex::Slot::Slot0) const;
        
        void unbind() const;
        
        [[nodiscard]] inline GAPI::UInt getWidth() const { return width; }
        
        [[nodiscard]] inline GAPI::UInt getHeight() const { return height; }
        
        [[nodiscard]] inline GAPI::Size getTotalOfPixels() const { return width * height; }
        
        [[nodiscard]] inline const std::string &getPath() const { return path; }
        
        [[nodiscard]] inline GAPI::UInt getTextureID() const { return textureID; }
        
        [[nodiscard]] Pixel getPixel(GAPI::UInt x, GAPI::UInt y) const;
        
        [[nodiscard]] const std::vector<GAPI::UByte> &getPixelsInBytes() const{ return pixels;}
        
        [[nodiscard]] const Format &getFormat() const;
        
        [[nodiscard]] std::string toString() const;
    
    
    private:
        
        GAPI::UInt textureID;
        GAPI::UInt width, height;
        std::vector<GAPI::UByte> pixels;
        std::shared_ptr<Format> format;
        std::string path;
        
        
        void initializeData(SDL_Surface &sdlSurface);
    }; // class Texture
}