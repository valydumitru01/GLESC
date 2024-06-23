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

    /**
     * @brief Class that loads and stores sounds and music.
     * @details Sounds and music are stored in maps that are accesed by their name.
     */
    class SoundLoader {
        friend class SoundPlayer;
        /**
         * @brief Initializes SDL and SDL_mixer.
         */
        static void init();
        /**
         * @brief Cleans up the resources used by SDL and SDL_mixer.
         */
        void cleanup();
        /**
         * @brief Loads a sound from a file.
         * @details The sound is stored in a map with the name as the key.
         * @param filePath The path to the sound file.
         * @param name The name of the sound.
         */
        void loadSound(const std::string& filePath, const std::string& name);
        /**
         * @brief Loads a music from a file.
         * @details The music is stored in a map with the name as the key.
         * @param filePath The path to the music file.
         * @param name The name of the music.
         */
        void loadMusic(const std::string& filePath, const std::string& name);
        /**
         * @brief Gets a sound by name.
         * @param name The name of the sound.
         * @return The sound.
         */
        Mix_Chunk& getSound(const std::string& name);
        /**
         * @brief Gets a music by name.
         * @param name The name of the music.
         * @return The music.
         */
        Mix_Music& getMusic(const std::string& name);


        static constexpr const char* soundsPath = SOUNDS_PATH"/";
        std::map<Hasher::Hash, Mix_Chunk*> sounds{};
        std::map<Hasher::Hash, Mix_Music*> music{};
    };
} // namespace GLESC
