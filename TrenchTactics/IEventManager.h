#pragma once

/// <summary>
/// IEventManager interface to achieve capsulation
/// </summary>
class IEventManager
{
public:
	virtual ~IEventManager(){}
	virtual void processEvents() = 0;

};

