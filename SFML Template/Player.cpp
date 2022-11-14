#include "Player.h"

enum MOVEMENT_KEYS {
	UP_KEY = 41
};

Player::Player()
{
	ID id("Player");
	id.color = Vec3f(50,0,200);
	id.id = 0;
	
	Entity::setID(id);
	Entity::setHeading(UP);

	setMovementKeys(Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D);
}

Player::~Player()
{
}

void Player::update(const double _DT)
{
	movement(_DT);
}

void Player::updatePosition(const double _DT)
{
	sf::Time updateMoveTime = updateMoveClock.getElapsedTime();
	if (updateMoveTime.asSeconds() > 0.1)
	{
		Entity::setPosition(Entity::getPosition() += Entity::getVelocity());
		updateMoveClock.restart();
	}
}

void Player::updateActions()
{
}

void Player::setMovementKeys(Keyboard::Key UP, Keyboard::Key DOWN, Keyboard::Key LEFT, Keyboard::Key RIGHT)
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

	if (Entity::getDirection() == DIRECTIONS::UP && sf::Keyboard::isKeyPressed(KEY_UP))
		Entity::setVelocity(Vec2i(0, -1));
	else if (Entity::getDirection() == DIRECTIONS::DOWN && sf::Keyboard::isKeyPressed(KEY_DOWN))
		Entity::setVelocity(Vec2i(0, 1));
	else if (Entity::getDirection() == DIRECTIONS::LEFT && sf::Keyboard::isKeyPressed(KEY_LEFT))
		Entity::setVelocity(Vec2i(-1, 0));
	else if (Entity::getDirection() == DIRECTIONS::RIGHT && sf::Keyboard::isKeyPressed(KEY_RIGHT))
		Entity::setVelocity(Vec2i(1, 0));
	else
		Entity::setVelocity(Vec2i(0, 0));
}
