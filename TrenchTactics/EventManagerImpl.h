#pragma once
#include "IEventManager.h"
#include "Singleton.hpp"

/// <summary>
/// EventManagerImpl class based on singelton pattern
/// for implementing the EventManager and handling events
/// </summary>
class EventManagerImpl :
	public IEventManager
{
public:
	EventManagerImpl(const EventManagerImpl&) = delete;
	EventManagerImpl& operator=(const EventManagerImpl&) = delete;
	EventManagerImpl(EventManagerImpl&&) = delete;
	EventManagerImpl& operator=(EventManagerImpl&&) = delete;

	~EventManagerImpl() {};
	void processEvents();

	static auto& instance() {
		static EventManagerImpl eventManager;
		return eventManager;
	}

private: 
	EventManagerImpl() {};
};

