#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	void update(const double _DT);
	void render(sf::RenderWindow& window);

private:
	
};

