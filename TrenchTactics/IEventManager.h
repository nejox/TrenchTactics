#pragma once
#include <SDL.h>
#include "EventBus.h"
#include "MouseClickEvent.h"
#include "EndGameEvent.h"
#include <iostream>
#include "Sprite.h"
#include "IngameMenuEvent.h"

/**
 * Event Manager Interface.
 */
class IEventManager
{
public:
	virtual ~IEventManager() {}
	virtual void processEvents() = 0;

};
