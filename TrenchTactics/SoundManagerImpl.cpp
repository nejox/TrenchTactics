#include "SoundManagerImpl.h"
#include "ConfigReader.h"
#include "RendererImpl.h"
#include "Logger.hpp"


/**
 * gracefully clean up audio variables
 */
SoundManagerImpl::~SoundManagerImpl()
{
	SDL_CloseAudioDevice(this->deviceId);
	SDL_FreeWAV(wavBuffer);

}


/**
 * start playing music
 */
void SoundManagerImpl::startMusic()
{
	std::string filePath =  ConfigReader::instance().getTechnicalConf()->getaudioFilePath();
	if (SDL_LoadWAV(filePath.c_str(), &wavSpec, &wavBuffer, &wavLength) == NULL) {
		std::string msg = "Fehler beim Laden von: " + filePath + "\n Fehlermeldung: ";
		msg.append(SDL_GetError());
		Logger::instance().log(LOGLEVEL::FATAL, msg);
		RendererImpl::instance().destroy();

		exit(1);
	}

	deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

	int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);
}

/**
 * stop playing music
 */
void SoundManagerImpl::stopMusic()
{
	SDL_PauseAudioDevice(deviceId, 1);
}
