#pragma once
#include "ID.h"
#include "ActionHandler.h"

class Entity
{
public:
	Entity();
	~Entity();

	//Gets
	ID getID() const { return entityID; }
	Vec2i getVelocity() const { return velocity; }
	int getDirectoin() const { return dir; }
	ActionHandler getActionHandler() const { return actionHandler; }

	//Sets
	void setVelocity(Vec2i _vel) { velocity = _vel; }


	virtual void update(const double _DT);
	virtual void updateActions();
	enum DIRECTIONS {UP, RIGHT, DOWN, LEFT};
	
protected:
	//Gets

	//Sets
	void setID(ID _ID) { entityID = _ID; }
	void setHeading(DIRECTIONS a) { dir = a; }

	ActionHandler actionHandler;

	virtual void movement(const double _DT);
	virtual void newAction(ACTIONS);
	
private:
	int dir;
	Vec2i velocity;
	ID entityID;
};
