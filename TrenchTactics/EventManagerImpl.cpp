#include "EventManagerImpl.h"
#include <SDL.h>
#include "EventBus.h"
#include "MouseClickEvent.h"
#include "EndGameEvent.h"
#include <iostream>
#include "Sprite.hpp"
#include "IngameMenuEvent.h"

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
			break;
		}
		case(SDL_QUIT): {
			bus.publish(new EndGameEvent());
			break;
		}

		case(SDL_KEYDOWN) : {
			switch (Event.key.keysym.sym)
			{
			case (SDLK_ESCAPE):
			{
				bus.publish(new IngameMenuEvent());

			} break;

			default:
				break;
			}
		}

		default:
			break;
		}

	}
}
