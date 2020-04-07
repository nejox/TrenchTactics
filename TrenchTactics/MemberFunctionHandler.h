#pragma once
#include "HandlerFunctionBase.h"

template<class T, class EventType>

class MemberFunctionHandler :
	public HandlerFunctionBase
{

public:
	typedef void (T::* MemberFunction)(EventType*);


	MemberFunctionHandler(T* instance, MemberFunction memberFunction)
	{
		this->instance = instance;
		this->memberFunction = memberFunction;
	}

	void call(Event* event)
	{
		// Casting event to the correct type & call memberFunction
		(instance->*memberFunction)(static_cast<EventType*>(event));
	}


private:

	T* instance;
	MemberFunction memberFunction;
};

