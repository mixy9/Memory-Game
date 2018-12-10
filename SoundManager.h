#pragma once

#include "stdafx.h"
#include "ResourceHolder.h"



class SoundManager
{
private:
	ResourceHolder<sf::SoundBuffer> soundBuffer;

	static SoundManager* instance;

	sf::Sound sound;
	sf::Music music;

	enum class MusicState
	{
		PLAYING,
		PAUSED
	};
	static MusicState currentState;

	SoundManager();

public:
	static SoundManager* getInstance();	

	void playSound(Resource::ID id, std::string filename);
	void playMusic(std::string filename);
	void pauseMusic();
	void stopMusic();

	bool isPaused();
	bool isPlaying();

	~SoundManager();
};


