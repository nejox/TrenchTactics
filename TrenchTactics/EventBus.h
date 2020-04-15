#pragma once
#include <map>
#include <typeindex>
#include <list>
#include "MemberFunctionHandler.h"
#include "Singleton.hpp"

//typedefs
//a list of handler objects
typedef std::list<HandlerFunctionBase*> HandlerList;

/// <summary>
/// EventBus class based on singelton pattern
/// for Event handling across modules
/// </summary>
class EventBus 
{
public:

	EventBus(const EventBus&) = delete;
	EventBus& operator=(const EventBus&) = delete;
	EventBus(EventBus&&) = delete;
	EventBus& operator=(EventBus&&) = delete;

	static auto& instance() {
		static EventBus eventBus;
		return eventBus;
	}

	/// <summary>
	/// Deconstructor to delete created lists 
	/// </summary>
	~EventBus()
	{
		std::map<std::type_index, HandlerList*>::iterator it = subscribers.begin();

		while (it != subscribers.end())
		{
			HandlerList* handlers = it->second;

			handlers->clear();
			delete handlers;
		}
	}



	template<typename EventType>
	/// <summary>
	/// publish method which publishes the event on the eventbus and calls every subscribed handler
	/// </summary>
	/// <param name="event">the raised event</param>
	void publish(EventType* event)
	{
		HandlerList* handlers = subscribers[typeid(EventType)];

		if (handlers == nullptr) {
			return;
		}

		for (auto& handler : *handlers) {
			if (handler != nullptr) {
				handler->exec(event);
			}
		}
	}

	template<class T, class EventType>
	/// <summary>
	/// subscribe  method which lets subscribe for an specific event
	/// </summary>
	/// <param name="instance">the class instance</param>
	/// <param name="memberFunction">the respective memberFunction which handles the event</param>
	void subscribe(T* instance, void (T::* memberFunction)(EventType*))
	{
		HandlerList* handlers = subscribers[typeid(EventType)];

		//first time init
		if (handlers == nullptr) {
			handlers = new HandlerList();
			subscribers[typeid(EventType)] = handlers;
		}

		handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
	}

private:

	EventBus() {};
	//Map of index and the List of handlers
	std::map<std::type_index, HandlerList*> subscribers;

};

