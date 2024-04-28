/**************************************************************************************************
 * @file   TextureSurface.h
 * @author Valentin Dumitru
 * @date   28/04/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <string>

#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "TextureStructs.h"

#define TEXTURE_EXTENSION ".png"

namespace GLESC::ResMng::Texture {
    class TextureSurface {
    public:
        /**
         * @brief Loader constructor. This constructor will initialize the texture with the data from the file.
         */
        TextureSurface(const std::string& pathParam);

        /**
         * @brief Default constructor. This will not initialize the texture, therefore you will need to call load() to load
         * the the data from the desired file.
         */
        TextureSurface() = default;

        ~TextureSurface() = default;
        void load(const std::string& pathParam);
        [[nodiscard]] unsigned int getHeight() const {
            return height;
        }

        [[nodiscard]] unsigned int getWidth() const {
            return width;
        }

        [[nodiscard]] const Format& getFormat() const {
            return format;
        }

        [[nodiscard]] const std::vector<UByte>& getPixels() const {
            return pixels;
        }

        [[nodiscard]] Size getTotalOfPixels() const { return width * height; }

        void initializeData(SDL_Surface& sdlSurface);


        [[nodiscard]] Pixel getPixel(unsigned int x, unsigned int y) const;

        [[nodiscard]] std::string toString() const;

    private:
        [[nodiscard]] static bool isDppCorrect(UInt bpp) {
            return bpp == 8 || bpp == 16 || bpp == 24 || bpp == 32;
        }

        UInt width{0};
        UInt height{0};
        std::vector<UByte> pixels{};
        Format format;
        bool hasLoaded = false;
    }; // class TextureSurface
} // namespace GLESC::ResMng::Texture
