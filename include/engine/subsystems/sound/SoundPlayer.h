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
    class SoundPlayer {
        using Channel = int;
        using Volume = int;
        using Loops = int;

    public:
        static void init();
        static void cleanup();
        static void loadSong(const std::string& filePath, const std::string& name);
        static void loadSound(const std::string& filePath, const std::string& name);
        static Channel playSound(const std::string& name, Volume volume = 128, Loops loops = 0);
        static void play3DSound(const std::string& name,
                                                 const Vec3F& listenerPos,
                                                 const Vec3F& soundPos);
        static void setMusic(const std::string& name);
        static void setMusicVolume(int volume);
        static void playMusic(Loops loops = -1, Volume volume = 128); // Default is to loop indefinitely

    private:
        static Mix_Music* currentMusic;
        static constexpr float maxDistance = 1000.0f;
        static SoundLoader soundLoader;
    };
}
