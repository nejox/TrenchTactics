#pragma once
#include "IEventManager.h"
#include "Singleton.hpp"

class EventManagerImpl :
	public IEventManager,
	public TSingleton<EventManagerImpl>
{
public:
	EventManagerImpl() {}
	~EventManagerImpl() {}
	void processEvents();
};

