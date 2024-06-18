/**************************************************************************************************
 * @file   SoundLoader.h
 * @author Valentin Dumitru
 * @date   13/06/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>

#include "engine/core/hash/Hasher.h"


namespace GLESC {
    class SoundPlayer;
    class SoundLoader {
        friend class SoundPlayer;
        static void init();
        void cleanup();
        void loadSound(const std::string& filePath, const std::string& name);
        void loadMusic(const std::string& filePath, const std::string& name);
        Mix_Chunk& getSound(const std::string& name);
        Mix_Music& getMusic(const std::string& name);


        static constexpr const char* soundsPath = SOUNDS_PATH"/";
        std::map<Hasher::Hash, Mix_Chunk*> sounds{};
        std::map<Hasher::Hash, Mix_Music*> music{};
    };
} // namespace GLESC
