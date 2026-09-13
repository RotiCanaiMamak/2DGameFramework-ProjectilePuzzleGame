#include "AudioManager.h"
#include <iostream>
using namespace std;

void Audio::initializeAudio()
{
    result = FMOD::System_Create(&system);
    result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
}

void Audio::playSound(const string& key, float pitch)
{
    auto sound = sounds.find(key);
    if (sound == sounds.end()) return;

    FMOD::Channel* soundchannel = nullptr;
    result = system->playSound(sound->second, 0, false, &soundchannel);
    
    if (soundchannel && pitch != 1.0f) {
        soundchannel->setPitch(pitch);
    }
    channels[key] = soundchannel;

}

void Audio::loadSounds(const string& key, string filename, bool loop)
{
   
    FMOD::Sound* sound = nullptr;
    result = system->createStream(filename.c_str(), FMOD_DEFAULT, 0, &sound);
    if (result != FMOD_OK) {
        cout << "Failed to load sound: " << filename << endl;
        return;
    }
    if (!loop) {
        sound->setMode(FMOD_LOOP_OFF);
        sounds[key] = sound;
    }
    else {
        sound->setMode(FMOD_LOOP_NORMAL);
        sounds[key] = sound;
    }
}

void Audio::updateSound()
{
    result = system->update();
}

void Audio::stopsound(const string& key) {
    auto sound = channels.find(key);
    if (sound != channels.end() && sound->second) {
        sound->second->stop();
    }
}

void Audio::stopallsound() {
    for (auto it = channels.begin(); it != channels.end(); ++it) {
        it->second->stop();
    }
    channels.clear();
}

float clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void Audio::setVolume(float vol)
{
    masterVolume = clamp(vol, 0.0f, 1.0f);
    for (auto it = channels.begin(); it != channels.end(); ++it) {
        if (it->second) it->second->setVolume(masterVolume);
    }
}


void Audio::increaseVolume()
{
    setVolume(masterVolume + 0.01f); // raise by 1%
}

void Audio::decreaseVolume()
{
    setVolume(masterVolume - 0.01f); // lower by 1%
}

void Audio::toggleSound()
{
    soundEnabled = !soundEnabled;

    for (auto it = channels.begin(); it != channels.end(); ++it) {
        if (it->second) it->second->setPaused(!soundEnabled);
    }

    soundState = soundEnabled ? "Unmute" : "Mute";

    cout << "Sound is now " << (soundEnabled ? "ON" : "OFF") << endl;
}
