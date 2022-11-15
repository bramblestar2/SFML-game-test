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
	Vec2i getPosition() const { return position; }
	Vec2i getChunkPosition() const { return chunkPosition; }
	int getDirection() const { return dir; }
	ActionHandler getActionHandler() { return actionHandler; }

	//Sets
	void setVelocity(Vec2i _vel) { velocity = _vel; }
	void setPosition(Vec2i a) { position = a; }
	virtual void updatePosition(const double _DT);


	virtual void update(const double _DT);
	virtual void updateActions();
	enum DIRECTIONS {UP, RIGHT, DOWN, LEFT};
	
protected:
	//Gets

	//Sets
	void setID(ID _ID) { entityID = _ID; }
	void setHeading(DIRECTIONS a) { dir = a; }
	void setChunkPosition();
	void move(Vec2i a) { position += a; }

	ActionHandler actionHandler;

	virtual void movement(const double _DT);
	virtual void newAction(ACTIONS);
	
private:
	int dir;
	Vec2i velocity;
	Vec2i position;
	Vec2i chunkPosition;
	ID entityID;
};
