/**************************************************************************************************
 * @file   SoundLoader.cpp
 * @author Valentin Dumitru
 * @date   13/06/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/res-mng/sounds/SoundLoader.h"

#include <SDL2/SDL.h>
#include "engine/core/asserts/Asserts.h"
#include "engine/core/file-system/BinPath.h"

using namespace GLESC;

void SoundLoader::init() {
    [[maybe_unused]] int err = SDL_Init(SDL_INIT_AUDIO);
    D_ASSERT_FALSE(err < 0,
                   std::string("SDL could not initialize! SDL Error: %s\n")+ SDL_GetError());
    [[maybe_unused]] err = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) ;
    D_ASSERT_FALSE(err < 0,
                   std::string("SDL_mixer could not initialize! SDL_mixer Error: %s\n") + Mix_GetError());
}


void SoundLoader::cleanup() {
    for (auto& sound : sounds) {
        Mix_FreeChunk(sound.second);
    }
    sounds.clear();

    for (auto& m : music) {
        Mix_FreeMusic(m.second);
    }
    music.clear();

    Mix_Quit();
}

void SoundLoader::loadSound(const std::string& filePath, const std::string& name) {
    std::string soundPath = BinPath::getExecutableDirectory() + soundsPath + filePath;
    Mix_Chunk* sound = Mix_LoadWAV(soundPath.c_str());
    D_ASSERT_NOT_NULLPTR(sound, "Failed to load sound: "+ soundPath);
    Hasher::Hash nameHash = Hasher::hash(name);
    sounds[nameHash] = sound;
}


void SoundLoader::loadMusic(const std::string& filePath, const std::string& name) {
    std::string songPath = BinPath::getExecutableDirectory() + soundsPath + filePath;
    Mix_Music* m = Mix_LoadMUS(songPath.c_str());
    D_ASSERT_NOT_NULLPTR(m, "Failed to load music: "+ songPath);
    Hasher::Hash nameHash = Hasher::hash(name);
    music[nameHash] = m;
}

Mix_Music& SoundLoader::getMusic(const std::string& name) {
    Hasher::Hash nameHash = Hasher::hash(name);
    D_ASSERT_TRUE(music.count(nameHash), "Music not found: "+ name);
    return *music[nameHash];
}

Mix_Chunk& SoundLoader::getSound(const std::string& name) {
    Hasher::Hash nameHash = Hasher::hash(name);
    D_ASSERT_TRUE(sounds.count(nameHash), "Sound not found: "+ name);
    return *sounds[nameHash];
}
