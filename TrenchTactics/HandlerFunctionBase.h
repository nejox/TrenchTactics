#pragma once
#include "Event.h"

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

