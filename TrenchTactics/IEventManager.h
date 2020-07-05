#pragma once


/**
 * Event Manager Interface.
 */
class IEventManager
{
public:
	virtual ~IEventManager() {}
	virtual void processEvents() = 0;

};
