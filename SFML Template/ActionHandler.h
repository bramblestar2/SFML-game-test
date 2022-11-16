#pragma once
#include <vector>
#include <iostream>

enum ACTIONS { 
	BREAK, 
	ATTACK,
	SELECTED_ITEM_CHANGED, 
	PLACED_BLOCK,
	ENTERED_NEW_CHUNK,
};

class ActionHandler
{
public:

	void push_back(ACTIONS a) { actionEvents.push_back(a); }
	bool poll_events(ActionHandler& a);
	bool poll_events();

	ACTIONS getEvent(ActionHandler& a) { 
		if (actionEvents.size() > 0)
		{
			currentEvent = a.actionEvents.at(actionEvents.size() - 1);
			remove_top_event(a);
		}
		return currentEvent; 
	}

	ACTIONS getEvent() {
		//remove_top_event(*this);
		if (actionEvents.size() > 0)
		{
			currentEvent = actionEvents.at(actionEvents.size() - 1);
			actionEvents.pop_back();
		}
		return currentEvent;
	}

private:
	void remove_top_event(ActionHandler& a) { a.actionEvents.pop_back(); }

	ACTIONS currentEvent;

	std::vector<ACTIONS> actionEvents;
};

