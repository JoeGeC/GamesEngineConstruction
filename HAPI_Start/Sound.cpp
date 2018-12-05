#include "Sound.h"

Sound::Sound(std::string soundName, std::string fileName) : m_soundName(soundName), m_fileName(fileName)
{

}

Sound::~Sound()
{
}

void Sound::LoadSound()
{
	if (!HAPI.LoadSound(m_fileName))
	HAPI.UserMessage("Could not load sound: " + m_fileName, "ERROR");
}

void Sound::PlaySound()
{
	HAPI.PlaySound(m_fileName);
}

void Sound::PlayStreamed()
{
	HAPI.PlayStreamedMedia(m_fileName);
}