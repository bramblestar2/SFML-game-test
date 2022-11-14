#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

using sf::Keyboard;

class Player : public Entity
{
public:
	Player();
	~Player();

	void update(const double _DT) override;
	void updatePosition(const double _DT) override;
	void updateActions() override;

	void setMovementKeys(Keyboard::Key, Keyboard::Key, Keyboard::Key, Keyboard::Key);

protected:

	void movement(const double _DT) override;

private:
	sf::Clock updateMoveClock;

	sf::Keyboard::Key KEY_UP;
	sf::Keyboard::Key KEY_DOWN;
	sf::Keyboard::Key KEY_LEFT;
	sf::Keyboard::Key KEY_RIGHT;
};

