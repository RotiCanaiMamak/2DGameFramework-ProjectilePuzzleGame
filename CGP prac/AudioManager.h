#pragma once
#include "fmod.hpp"
#include <map>
#include <string>

using namespace std;

class Audio
{

public:
	FMOD::System* system; //similar to Direct3d Device, this is our virtual soundcard
	FMOD_RESULT result; //similar to HRESULT, for handling error codes
	void* extradriverdata = 0; //literally nothing
	
	//Sound* similar to texture, actual sound file loaded into sound card memory
	//FMOD::Sound* sound1, * sound2, * mainmenubgm, * shortsound, * gameoversound, * gameoversoundbgm, * mainmenusounduibtn; 
	//use map high scalability
	map<string, FMOD::Sound*> sounds;

	//a bit similar to buffer, where the audio is played through a channel
	//FMOD::Channel* channel = 0; 
	map<string, FMOD::Channel*> channels;

	static Audio& getInstance() {
		static Audio instance;
		return instance;
	}

	void initializeAudio(); //to setup the virtual sound card
	void playSound(const string& key, float pitch);
	void loadSounds(const string& key, string filename, bool loop); //load sounds into memory
	void updateSound(); //apply the processing to the sound channel
	void stopsound(const string& key);

	float masterVolume = 0.9f;
	void setVolume(float vol);
	bool soundEnabled = true;
	string soundState = "Mute";
	void toggleSound();
	void increaseVolume();
	void decreaseVolume();
	void stopallsound();
};


