#pragma once
#include "HandlerFunctionBase.h"

//template
template<class T, class EventType>

/// <summary>
/// MemberFunctionHandler class for implementing HandlerFunctionBase
/// calls the member function of the respective class instance 
/// </summary>
class MemberFunctionHandler :
	public HandlerFunctionBase
{

public:
	typedef void (T::* MemberFunction)(EventType*);

	/// <summary>
	/// specialised constructor to create the handler objects
	/// </summary>
	/// <param name="instance">the class instance</param>
	/// <param name="memberFunction">the respective member function for handling the event</param>
	MemberFunctionHandler(T* instance, MemberFunction memberFunction)
	{
		this->instance = instance;
		this->memberFunction = memberFunction;
	}

	/// <summary>
	/// calls the member function if event is raised
	/// </summary>
	/// <param name="event">the raised event</param>
	void call(Event* event)
	{
		// Casting event to the correct type & call memberFunction
		(instance->*memberFunction)(static_cast<EventType*>(event));
	}

private:

	T* instance;
	MemberFunction memberFunction;
};

