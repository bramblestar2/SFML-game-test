#include "Game.h"
#include <math.h>

Game::Game()
{
	window = nullptr;
	
	entities.push_back(new Player());
}

Game::~Game()
{
	for (int i = 0; i < entities.size(); i++)
		delete entities.at(i);
}

void Game::setWindowPtr(sf::RenderWindow* window)
{
	this->window = window;
	camera = CustomView(sf::Vector2f(0, 0), sf::Vector2f(window->getSize()));
	camera.setTransitionSpeed(0.1f);
	camera.smoothTransition(true);
}

void Game::update(const double _DT)
{
	if (window != nullptr)
	{
		camera.update(_DT);
		window->setView(camera.getView());

		for (int i = 0; i < entities.size(); i++)
		{
			
			entities.at(i)->update(_DT);
			entities.at(i)->updatePosition(_DT);

			if (entities.at(i)->getID().getType() == "Player")
			{
				Vec2i pos = entities.at(i)->getPosition();
				camera.moveTo(sf::Vector2f(pos.x * 20, pos.y * 20));
			}

			//Check the type and update accordingly
			for (int k = 0; k < entities.size(); k++)
			{
				if (k != i)
				{
					if (entities.at(k)->getID().getType() == "Player")
					{
						
					}
					else if (entities.at(k)->getID().getType() == "Enemy")
					{

					}
				}
			}
		}
	}
}

void Game::updateSFMLEvents(sf::Event event, const double _DT)
{
	if (window != nullptr)
	{
		if (event.type == sf::Event::MouseMoved)
		{
			//Follow mouse
			//camera.moveTo(sf::Vector2f(sf::Mouse::getPosition(*window)));
		}
	}
}

void Game::render()
{
	if (window != nullptr)
	{

		for (int i = 0; i < entities.size(); i++)
		{
			sf::RectangleShape entityShape;
			entityShape.setSize(sf::Vector2f(20, 20));
			entityShape.setOrigin(entityShape.getSize().x/2, entityShape.getSize().y/2);

			entityShape.setPosition(entities.at(i)->getPosition().x * 20, 
									entities.at(i)->getPosition().y * 20);

			entityShape.setFillColor(sf::Color(
				entities.at(i)->getID().color.x,
				entities.at(i)->getID().color.y,
				entities.at(i)->getID().color.z
			));



			window->draw(entityShape);

			sf::VertexArray visibleHeading(sf::TriangleFan, 3);
			for (int i = 0; i < 3; i++)
				visibleHeading[i].color = sf::Color(255, 255, 255, 100);

			visibleHeading[0].position = entityShape.getPosition();
			sf::Vector2f topLeft, topRight, bottomLeft, bottomRight;
			
			topLeft = sf::Vector2f(entityShape.getPosition().x - (entityShape.getSize().x / 3),
								   entityShape.getPosition().y - (entityShape.getSize().y / 3));
			topRight = sf::Vector2f(entityShape.getPosition().x + (entityShape.getSize().x / 3),
									entityShape.getPosition().y - (entityShape.getSize().y / 3));
			bottomLeft = sf::Vector2f(entityShape.getPosition().x - (entityShape.getSize().x / 3),
									  entityShape.getPosition().y + (entityShape.getSize().y / 3));
			bottomRight = sf::Vector2f(entityShape.getPosition().x + (entityShape.getSize().x / 3),
									   entityShape.getPosition().y + (entityShape.getSize().y / 3));

			if (entities.at(i)->getDirection() == Entity::UP)
			{
				//top left corner of cube
				visibleHeading[1].position = topLeft;
				//top right corner of cube
				visibleHeading[2].position = topRight;
			}
			else if (entities.at(i)->getDirection() == Entity::RIGHT)
			{
				//Top right
				visibleHeading[1].position = topRight;
				//Bottom right
				visibleHeading[2].position = bottomRight;
			}
			else if (entities.at(i)->getDirection() == Entity::DOWN)
			{
				//Bottom right
				visibleHeading[1].position = bottomRight;
				//Bottom left
				visibleHeading[2].position = bottomLeft;
			}
			else if (entities.at(i)->getDirection() == Entity::LEFT)
			{
				//Top left
				visibleHeading[1].position = topLeft;
				//Bottom left
				visibleHeading[2].position = bottomLeft;
			}


			window->draw(visibleHeading);
		}
	}
}

bool Game::checkDistance(const Vec2i position, const Vec2i positionToCheck, const float distance)
{
	float pointX = pow(positionToCheck.x - position.x, 2);
	float pointY = pow(positionToCheck.y - position.y, 2);
	float distanceAway = sqrt(pointX + pointY);

	if (distanceAway <= distance)
		return true;

	return false;
}
