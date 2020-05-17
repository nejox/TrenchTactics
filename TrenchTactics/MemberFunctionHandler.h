#pragma once
#include "HandlerFunctionBase.h"

//template
template<class T, class EventType>

/**
 * MemberFunctionHandler class for implementing HandlerFunctionBase.
 * calls the member function of the respective class instance
 */
class MemberFunctionHandler :
	public HandlerFunctionBase
{

public:
	typedef void (T::* MemberFunction)(EventType*);

	/**
	 * specialised constructor to create the handler objects.
	 *
	 * \param instance the class instance
	 * \param memberFunction the respective member function for handling the event
	 */
	MemberFunctionHandler(T* instance, MemberFunction memberFunction)
	{
		this->instance = instance;
		this->memberFunction = memberFunction;
	}

	/**
	 * calls the member function if event is raised.
	 *
	 * \param event the raised event
	 */
	void call(Event* event)
	{
		// Casting event to the correct type & call memberFunction
		(instance->*memberFunction)(static_cast<EventType*>(event));
	}

private:

	T* instance;
	MemberFunction memberFunction;
};

