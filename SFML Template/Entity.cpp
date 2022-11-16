#include "Entity.h"

Entity::Entity()
{
	dir = UP;
}

Entity::~Entity()
{
}

void Entity::updatePosition(const double _DT)
{
}

void Entity::update(const double _DT)
{

}

void Entity::updateActions()
{
}

void Entity::setChunkPosition()
{
	//20 x 20 chunks
	chunkPosition.x = position.x / 10;
	chunkPosition.y = position.y / 10;

	if (prevChunkPosition != chunkPosition)
	{
		actionHandler.push_back(ACTIONS::ENTERED_NEW_CHUNK);
		prevChunkPosition = chunkPosition;
	}
}

void Entity::movement(const double _DT)
{

}

void Entity::newAction(ACTIONS action)
{
	actionHandler.push_back(action);
}
