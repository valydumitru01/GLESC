
#include "engine/subsystems/sound/SoundPlayer.h"
#include "engine/res-mng/sounds/SoundLoader.h"
#include "engine/subsystems/transform/Transform.h"

using namespace GLESC;

Mix_Music* SoundPlayer::currentMusic = nullptr;
SoundLoader SoundPlayer::soundLoader{};

void SoundPlayer::init() {
    SoundLoader::init();
}

void SoundPlayer::cleanup() {
    soundLoader.cleanup();
}

void SoundPlayer::loadSong(const std::string& filePath, const std::string& name) {
    soundLoader.loadMusic(filePath, name);
}

void SoundPlayer::loadSound(const std::string& filePath, const std::string& name) {
    soundLoader.loadSound(filePath, name);
}


SoundPlayer::Channel SoundPlayer::playSound(const std::string& name, Volume volume, Loops loops) {
    setMusicVolume(volume);
    Mix_Chunk& sound = soundLoader.getSound(name);
    return Mix_PlayChannel(-1, &sound, loops); // Play on the first free channel
}


void SoundPlayer::play3DSound(const std::string& name,
                              const Vec3F& listenerPos,
                              const Vec3F& soundPos) {
    // Calculate the distance between the listener and the sound
    Vec3F diff = soundPos - listenerPos;
    float distance = diff.length();

    // Assuming maxDistance is the distance at which the sound is inaudible
    const float maxDistance = 100.0f;
    float volume = (maxDistance - distance) / maxDistance;
    volume = std::max(0.0f, std::min(1.0f, volume));

    // Calculate the panning based on the relative position on the x-axis
    float pan = diff.getX() / maxDistance;
    pan = std::max(-1.0f, std::min(1.0f, pan));

    // Convert volume and pan to SDL_mixer's format
    int sdlVolume = static_cast<int>(volume * MIX_MAX_VOLUME);
    int left = static_cast<int>((1.0f - pan) * static_cast<float>(sdlVolume));
    int right = static_cast<int>((1.0f + pan) * static_cast<float>(sdlVolume));

    Channel channel = playSound(name, sdlVolume);
    Mix_SetPanning(channel, left, right);
}

void SoundPlayer::setMusic(const std::string& name) {
    Mix_Music& music = soundLoader.getMusic(name);
    currentMusic = &music;
}

void SoundPlayer::playMusic(Loops loops, Volume volume) {
    D_ASSERT_NOT_NULLPTR(currentMusic, "No music set to play");
    Mix_PlayMusic(currentMusic, loops);
    setMusicVolume(volume);
}

void SoundPlayer::setMusicVolume(Volume volume) {
    Mix_VolumeMusic(volume);
}
