#include "SoundManager.h"


// Initializing static variables
SoundManager* SoundManager::instance = nullptr;
SoundManager::MusicState SoundManager::currentState = MusicState::PLAYING;

SoundManager::SoundManager()
{
}

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
	m_soundBuffer.load(id, filename);
	m_sound.setBuffer(*m_soundBuffer.get(filename));
	m_sound.play();
	m_sound.setPitch(3);
	m_sound.setVolume(20);
}

void SoundManager::playMusic(std::string filename)
{
	if (isPlaying())
	{
		if (!m_music.openFromFile(filename))
			throw std::runtime_error("Error! Failed to open file " + filename);
		m_music.play(); 
		m_music.setVolume(20);
		m_music.setLoop(true);		
	}
}

void SoundManager::pauseMusic()
{
	m_music.pause();		
}

void SoundManager::stopMusic()
{
	m_music.stop();
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
