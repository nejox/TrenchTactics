#pragma once
#include <map>
#include <typeindex>
#include <list>
#include "MemberFunctionHandler.h"
#include "Singleton.hpp"

typedef std::list<HandlerFunctionBase*> HandlerList;
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
	std::map<std::type_index, HandlerList*> subscribers;

};

