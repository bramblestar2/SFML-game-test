#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	void update(const double _DT);
	void updateSFMLEvents(const double _DT);
	void render(sf::RenderWindow& window);

	sf::Vector2f getCurrentTracking() const { return trackingPos; }
private:
	sf::Vector2f trackingPos;
};

