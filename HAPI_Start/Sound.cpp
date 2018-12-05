#include "Sound.h"

Sound::Sound()
{
}

Sound::~Sound()
{
}

void Sound::LoadSound(std::string fileName)
{
	HAPI.LoadSound(fileName);
}