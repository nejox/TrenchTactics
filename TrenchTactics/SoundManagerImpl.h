#pragma once
#include "ISoundManager.h"
#include <SDL_audio.h>

/**
 * SoundManagerImpl class based on singelton pattern
 * for implementing the SoundManager and handling events
 */
class SoundManagerImpl :
	public ISoundManager
{
public:
	SoundManagerImpl(const SoundManagerImpl&) = delete;
	SoundManagerImpl& operator=(const SoundManagerImpl&) = delete;
	SoundManagerImpl(SoundManagerImpl&&) = delete;
	SoundManagerImpl& operator=(SoundManagerImpl&&) = delete;

	~SoundManagerImpl();
	
	void startMusic();
	void stopMusic();

	static auto& instance() {
		static SoundManagerImpl soundManager;
		return soundManager;
	}

private:
	Mix_Music* music;

	SoundManagerImpl() {
		this->music = NULL;
	};
};


