#pragma once
#include <vector>
#include <iostream>

enum ACTIONS { MOVE, BREAK, ATTACK, DIRECTION_CHANGE };

class ActionHandler
{
public:

	void push_back(ACTIONS a) { actionEvents.push_back(a); }
	bool poll_events(ActionHandler a) const { return !a.actionEvents.empty(); };

	ACTIONS getEvent(ActionHandler a) { 
		remove_top_event(a);
		return a.actionEvents.at(a.actionEvents.size() - 1); 
	}

	ACTIONS getEvent() {
		remove_top_event(*this);
		return actionEvents.at(actionEvents.size() - 1);
	}

private:
	void remove_top_event(ActionHandler a) { a.actionEvents.pop_back(); }

	std::vector<ACTIONS> actionEvents;
};

