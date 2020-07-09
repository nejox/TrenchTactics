#include "SoundManagerImpl.h"
#include "ConfigReader.h"
#include "RendererImpl.h"
#include "Logger.hpp"
#include <SDL_mixer.h>


/**
 * gracefully clean up audio variables
 */
SoundManagerImpl::~SoundManagerImpl()
{
}

/**
 * start playing music
 */
void SoundManagerImpl::startMusic()
{
	
	std::string filePath =  ConfigReader::instance().getTechnicalConf()->getaudioFilePath();

	Mix_OpenAudio(42050, AUDIO_S16SYS, 1, 640);
	music = Mix_LoadMUS(filePath.c_str());
	Mix_PlayMusic(music, -1);

}


/**
 * stop playing music
 */
void SoundManagerImpl::stopMusic()
{
	Mix_FreeMusic(music);
}
