#include "EventManagerImpl.h"
#include <SDL.h>
#include "EventBus.h"
#include "MouseClickEvent.h"
#include "EndGameEvent.h"
#include <iostream>


/**
 * EventmanagerImpl based on sdl functionality
 * Processes the mouse click events and publishes the corresponding mouse click event on to the EventBus
 *
 */
void EventManagerImpl::processEvents()
{
	SDL_Event Event;
	EventBus& bus = EventBus::instance();

	// Event raised?
	if (SDL_PollEvent(&Event)) {

		// which one?
		switch (Event.type)
		{

		case(SDL_MOUSEBUTTONDOWN): {

			// populate coordinates of mouse click
			int x, y;
			SDL_GetMouseState(&x, &y);
			// call mouse click handlers
			bus.publish(new MouseClickEvent(x, y));
		}
		case(SDL_QUIT): {
			std::cout << Event.type << std::endl;
			//bus.publish(new EndGameEvent());
		}

		default:
			break;
		}

	}
}
