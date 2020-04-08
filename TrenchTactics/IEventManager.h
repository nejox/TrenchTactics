#pragma once
class IEventManager
{
public:
	virtual ~IEventManager(){}
	virtual void processEvents() = 0;

};

