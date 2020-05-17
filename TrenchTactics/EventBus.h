#pragma once
#include <map>
#include <typeindex>
#include <list>
#include "MemberFunctionHandler.h"
#include "Singleton.hpp"

//typedefs
//a list of handler objects
typedef std::list<HandlerFunctionBase*> HandlerList;


/**
 * EventBus class based on singelton pattern
 * for Event handling across modules
 */
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

	/**
	 * Deconstructor to delete created map containing all subscriber functions
	 *
	 */
	~EventBus()
	{
		std::map<std::type_index, HandlerList*>::iterator it = subscribers.begin();

		while (it != subscribers.end())
		{
			HandlerList* handlers = it->second;

			handlers->clear();
			delete handlers;
			it++;
		}
	}

	template<typename EventType>
	/**
	 * Publish method that takes an event and publishes it to all subscribers with their respective handler function
	 *
	 * \param event
	 */
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
	/**
	 * Subscriber function that allows to subscribe to a specific type of event
	 *
	 * \param instance the class instance that contains the handler function
	 * \param memberFunction the respective memberFunction which handles the event
	 */
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

