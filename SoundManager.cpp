#include "SoundManager.h"


// Initializing static variables
SoundManager* SoundManager::instance = nullptr;
SoundManager::MusicState SoundManager::currentState = MusicState::PLAYING;


SoundManager::SoundManager() { }

SoundManager* SoundManager::getInstance()
{
	if (instance == 0)
	{
		instance = new SoundManager;
	}
	return instance;
}

void SoundManager::playSound(Resource::ID id, std::string filename)
{
	soundBuffer.load(id, filename);
	sound.setBuffer(*soundBuffer.get(filename));
	sound.play();
	sound.setVolume(20);
	sound.setPitch(3);
}

void SoundManager::playMusic(std::string filename)
{
	if (isPlaying())
	{
		if (!music.openFromFile(filename))
			throw std::runtime_error("Error! Failed to open file " + filename);
		music.play();
		music.setVolume(20);
		music.setLoop(true);		
	}
}

void SoundManager::pauseMusic()
{
	music.pause();		
}

void SoundManager::stopMusic()
{
	music.stop();
}

bool SoundManager::isPaused() 
{ 
	return currentState == MusicState::PAUSED;
}

bool SoundManager::isPlaying() 
{ 
	return currentState == MusicState::PLAYING;
}

SoundManager::~SoundManager()
{
	if (instance)
		delete instance;
}
