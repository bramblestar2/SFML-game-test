#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "CustomView.h"
#include "Player.h"

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
	CustomView camera;

	std::vector<Entity*> entities;
	Player player;
	
	sf::RectangleShape a;

	sf::RenderWindow* window;

	//Returns true if positionToCheck is in distance of position
	bool checkDistance(const Vec2i position, const Vec2i positionToCheck, const float distance);
};

