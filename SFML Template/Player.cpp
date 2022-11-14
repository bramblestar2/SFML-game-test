#include "Player.h"

enum MOVEMENT_KEYS {
	UP_KEY = 41
};

Player::Player()
{
	ID id("Player");
	id.color = Vec3f();
	id.id = 0;
	
	Entity::setID(id);
	Entity::setHeading(UP);

	set_key_config(Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D);
}

Player::~Player()
{
}

void Player::update(const double _DT)
{
}

void Player::updateActions()
{
}

void Player::set_key_config(Keyboard::Key UP, Keyboard::Key DOWN, Keyboard::Key LEFT, Keyboard::Key RIGHT)
{
	KEY_UP = UP;
	KEY_DOWN = DOWN;
	KEY_LEFT = LEFT;
	KEY_RIGHT = RIGHT;
}

void Player::movement(const double _DT)
{
	if (sf::Keyboard::isKeyPressed(KEY_UP))
	{
		newAction(ACTIONS::DIRECTION_CHANGE);
		Entity::setHeading(DIRECTIONS::UP);
	}
	else if (sf::Keyboard::isKeyPressed(KEY_DOWN))
	{
		newAction(ACTIONS::DIRECTION_CHANGE);
		Entity::setHeading(DIRECTIONS::DOWN);
	}
	else if (sf::Keyboard::isKeyPressed(KEY_LEFT))
	{
		newAction(ACTIONS::DIRECTION_CHANGE);
		Entity::setHeading(DIRECTIONS::LEFT);
	}
	else if (sf::Keyboard::isKeyPressed(KEY_RIGHT))
	{
		newAction(ACTIONS::DIRECTION_CHANGE);
		Entity::setHeading(DIRECTIONS::RIGHT);
	}
}
