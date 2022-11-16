#pragma once
#include "ID.h"
class Block
{
public:
	Block(Vec2i pos, float brightness);
	Block(Vec2i pos);
	Block();
	~Block();

	//Gets
	Vec2i getPosition() const { return position; }
	ID getID() const { return id; }
	//Sets
	void setPosition(Vec2i pos) { position = pos; }
	void setID(ID _id) { id = _id; }
	
	virtual void update();
	bool isBroken();
	virtual void changeBrightness(const float value);

	void HSVtoRGB(float H, float S, float V, float& R, float& G, float& B);
protected:

	
private:

	Vec2i position;
	ID id;

	//0 : Not broken ...
	//0.5 : Half broken ...
	//1 : Broken
	float breakPercentage;

	friend std::fstream& operator<<(std::fstream& a, const Block& block)
	{
		a << block.getID() << " " << block.getPosition().x << " " 
		  << block.getPosition().y << " " << block.breakPercentage;
		return a;
	}
};

