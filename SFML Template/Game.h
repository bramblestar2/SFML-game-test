#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "CustomView.h"
#include "Player.h"
#include "Block.h"

class Game
{
public:
	Game();
	~Game();

	void setWindowPtr(sf::RenderWindow* window);

	void update(const double _DT);
	void updateSFMLEvents(sf::Event event, const double _DT);
	void render();

private:
	void handleActions(Entity*);

	CustomView camera;

	std::vector<Entity*> entities;
	std::vector<Block*> blocks;
	int selectedBlockID;
	
	sf::RectangleShape a;

	sf::RenderWindow* window;

	//Returns true if block has been placed
	bool placeBlock(Vec2i);
	//Returns true if block has been destroyed
	bool destroyBlock(Vec2i);

	//load the chunk that the player is in and
	//load the chunks that are adjacent
	void chunkLoader();
	//Load the chunk that is given
	void loadChunk(Vec2i);
	void saveChunkData();
	Vec2i prevChunk; //The previous chunk the player was in

	//Returns true if positionToCheck is in distance of position
	bool checkDistance(const Vec2i position, const Vec2i positionToCheck, const float distance);
	bool willCollide(const Vec2i distance, Entity::DIRECTIONS moveNext);
	int blockInFrontEntity(const Vec2i distance, Entity::DIRECTIONS moveNext);

	void deleteBlock(int);
};

