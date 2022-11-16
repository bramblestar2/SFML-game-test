#include "ActionHandler.h"

bool ActionHandler::poll_events(ActionHandler& a)
{
	bool empty = a.actionEvents.empty();
	if (!empty)
	{
		currentEvent = a.actionEvents.at(a.actionEvents.size() - 1);
		a.actionEvents.pop_back();
	}
	return !empty;
}

bool ActionHandler::poll_events()
{
	bool empty = actionEvents.empty();
	if (!empty)
	{
		currentEvent = actionEvents.at(actionEvents.size() - 1);
		actionEvents.pop_back();
	}
	return !empty;
}
