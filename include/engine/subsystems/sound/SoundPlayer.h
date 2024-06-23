/**************************************************************************************************
 * @file   SoundPlayer.h
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

#include "engine/core/math/algebra/vector/Vector.h"
#include "engine/res-mng/sounds/SoundLoader.h"

namespace GLESC {
    /**
     * @brief Class that handles sound playing
     * @details This class handles all the playing and loading of sounds and music.
     * It provides a general interface for the game to facilitate sound playing.
     */
    class SoundPlayer {
        using Channel = int;
        using Volume = int;
        using Loops = int;

    public:
        /**
         * @brief Initialize the sound player
         */
        static void init();
        /**
         * @brief Cleanup the sound player
         */
        static void cleanup();
        /**
         * @brief Load a song from a file
         * @param filePath The path to the song file
         * @param name The name of the song
         */
        static void loadSong(const std::string& filePath, const std::string& name);
        /**
         * @brief Load a sound from a file
         * @param filePath The path to the sound file
         * @param name The name of the sound
         */
        static void loadSound(const std::string& filePath, const std::string& name);
        /**
         * @brief Play a sound
         * @details It must be loaded before playing
         * @param name The name of the sound
         * @param volume The volume of the sound
         * @param loops The number of times to loop the sound
         * @return The channel the sound is playing on
         */
        static Channel playSound(const std::string& name, Volume volume = 128, Loops loops = 0);
        /**
         * @brief Play a 3D sound
         * @details It must be loaded before playing
         * It will be played at the position of the sound and the listener taking advantage of the headphones
         * capabilities of playing sounds left and right
         * @param name The name of the sound
         * @param listenerPos The position of the listener
         * @param soundPos The position of the sound
         */
        static void play3DSound(const std::string& name,
                                                 const Vec3F& listenerPos,
                                                 const Vec3F& soundPos);
        /**
         * @brief Set the music to play
         * @param name The name of the music
         */
        static void setMusic(const std::string& name);
        /**
         * @brief Set the volume of the music
         * @param volume The volume of the music
         */
        static void setMusicVolume(int volume);
        /**
         * @brief Play the music
         * @details The music must have been loaded and set before playing
         * @param loops The number of times to loop the music
         * @param volume The volume of the music
         */
        static void playMusic(Loops loops = -1, Volume volume = 128); // Default is to loop indefinitely

    private:
        static Mix_Music* currentMusic;
        static constexpr float maxDistance = 1000.0f;
        static SoundLoader soundLoader;
    };
}
