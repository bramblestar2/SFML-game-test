#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

using sf::Keyboard;

class Player : protected Entity
{
public:
	Player();
	~Player();

	void update(const double _DT) override;
	void updateActions() override;

	void set_key_config(Keyboard::Key, Keyboard::Key, Keyboard::Key, Keyboard::Key);

protected:

	void movement(const double _DT) override;

private:
	sf::Keyboard::Key KEY_UP;
	sf::Keyboard::Key KEY_DOWN;
	sf::Keyboard::Key KEY_LEFT;
	sf::Keyboard::Key KEY_RIGHT;
};

