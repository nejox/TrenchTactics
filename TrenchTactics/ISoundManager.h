#pragma once

/**
 * Sound Manager Interface.
 */
class ISoundManager
{
public:
	virtual ~ISoundManager() {}
	virtual void startMusic() = 0;
	virtual void stopMusic() = 0;

};
