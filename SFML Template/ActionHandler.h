#pragma once
#include <vector>
#include <iostream>
class ActionHandler
{
public:
	enum ACTIONS { MOVE, BREAK, ATTACK };

	void push_back(ACTIONS a) { actionEvents.push_back(a); }
	bool poll_events() const { return !actionEvents.empty(); };

	ACTIONS getEvent() const { return actionEvents.at(actionEvents.size() - 1); }

private:
	void remove_top_event() { actionEvents.pop_back(); }

	std::vector<ACTIONS> actionEvents;
};

