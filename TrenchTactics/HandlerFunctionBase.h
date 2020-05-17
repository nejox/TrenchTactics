#pragma once
#include "Event.h"

/**
 * Base template for a handler function.
 */
class HandlerFunctionBase
{
public:
	// Calls the member function
	void exec(Event* event) {
		call(event);
	}

private:
	virtual void call(Event* event) = 0;

};

