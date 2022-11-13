#pragma once
#include "ID.h"

class Entity
{
public:
	Entity();
	~Entity();

	//Gets
	ID getID() const { return entityID; }
	Vec2i getVelocity() const { return velocity; }
	int getDirectoin() const { return dir; }

	//Sets
	void setVelocity(Vec2i _vel) { velocity = _vel; }


	void update();
	void updateActions();
	enum DIRECTIONS {UP, RIGHT, DOWN, LEFT};
	

protected:
	//Gets

	//Sets
	void setID(ID _ID) { entityID = _ID; }
	void setHeading(DIRECTIONS a) { dir = a; }

private:
	int dir;
	Vec2i velocity;
	ID entityID;

};
