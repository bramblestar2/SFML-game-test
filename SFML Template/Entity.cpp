#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::update(const double _DT)
{

}

void Entity::updateActions()
{
}

void Entity::movement(const double _DT)
{

}

void Entity::newAction(ACTIONS action)
{
	actionHandler.push_back(action);
}
