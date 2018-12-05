#pragma once

#include <string>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Sound
{
public:
	Sound(std::string soundName, std::string fileName);
	~Sound();
	void LoadSound();
	void PlaySound();
	void PlayStreamed();
	std::string GetName() const { return m_soundName; }
	std::string GetFileName() const { return m_fileName; }

private:
	std::string m_soundName;
	std::string m_fileName;
};

