#include "Game.h"
#include <math.h>

Game::Game()
{
	window = nullptr;

	entities.push_back(new Player());
	selectedBlockID = 0;
}

Game::~Game()
{
	for (int i = 0; i < entities.size(); i++)
		delete entities.at(i);
	for (int i = 0; i < blocks.size(); i++)
		delete blocks.at(i);
}

void Game::setWindowPtr(sf::RenderWindow* window)
{
	this->window = window;
	camera = CustomView(sf::Vector2f(0, 0), sf::Vector2f(window->getSize()));
	camera.setTransitionSpeed(0.03f);
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

			bool canMove = true;
			for (int k = 0; k < blocks.size(); k++)
			{
				bool inDistanceOne = checkDistance(entities.at(i)->getPosition(), blocks.at(k)->getPosition(), 20.f);
				
				if (inDistanceOne)
				{
					bool inDistanceTwo = checkDistance(entities.at(i)->getPosition(), blocks.at(k)->getPosition(), 5.f);

					int xDistance = blocks.at(k)->getPosition().x - entities.at(i)->getPosition().x;
					int yDistance = blocks.at(k)->getPosition().y - entities.at(i)->getPosition().y;
					float distance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
					
					if (blocks.at(k)->getID().id == 0)
						blocks.at(k)->changeBrightness((1 / distance) * 100);
					else if (blocks.at(k)->getID().id == 1)
						blocks.at(k)->changeBrightness((1/distance) * 30);

					if (inDistanceTwo)
					{

						//Brightness of block
						//Uses the distance from the player

						if (canMove && blocks.at(k)->getID().id != 1)
						{
							Entity::DIRECTIONS dir = Entity::UP;
							if (entities.at(i)->getDirection() == Entity::UP)
								dir = Entity::UP;
							else if (entities.at(i)->getDirection() == Entity::DOWN)
								dir = Entity::DOWN;
							else if (entities.at(i)->getDirection() == Entity::LEFT)
								dir = Entity::LEFT;
							else if (entities.at(i)->getDirection() == Entity::RIGHT)
								dir = Entity::RIGHT;

							canMove = !willCollide(Vec2i(xDistance, yDistance), dir);
						}
					}
				}
			}
			if (canMove)
				entities.at(i)->updatePosition(_DT);

			if (entities.at(i)->getID().getType() == "Player")
			{
				Vec2i pos = entities.at(i)->getPosition();
				camera.moveTo(sf::Vector2f(pos.x * 20, pos.y * 20));
			}


			//Check the type and update accordingly
			//for (int k = 0; k < entities.size(); k++)
			//{
			//	if (k != i)
			//	{
			//		if (entities.at(k)->getID().getType() == "Player")
			//		{
			//			
			//		}
			//		else if (entities.at(k)->getID().getType() == "Enemy")
			//		{
			//
			//		}
			//	}
			//}
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

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left)
			{
				if (selectedBlockID > 0)
					selectedBlockID--;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				if (selectedBlockID < 1)
					selectedBlockID++;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
			Vec2i point(round((mousePos.x) / 20), round((mousePos.y) / 20));

			if (event.mouseButton.button == sf::Mouse::Left)
			{
				bool canPlace = true;
				
				for (int i = 0; i < blocks.size() && canPlace; i++)
				{
					canPlace = !(blocks.at(i)->getPosition() == point);
					for (int k = 0; k < entities.size() && canPlace; k++)
						canPlace = !(entities.at(k)->getPosition() == point);
				}

				if (canPlace)
				{
					blocks.push_back(new Block(point));
					ID id = blocks.at(blocks.size() - 1)->getID();
					id.id = selectedBlockID;
					blocks.at(blocks.size() - 1)->setID(id);
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				for (int i = 0; i < blocks.size(); i++)
				{
					if (blocks.at(i)->getPosition() == point)
					{
						delete blocks.at(i);
						blocks.erase(blocks.begin() + i);
						break;
					}
				}
			}
		}
	}
}

void Game::render()
{
	if (window != nullptr)
	{
		for (int i = 0; i < blocks.size(); i++)
		{
			sf::RectangleShape blockShape;
			blockShape.setSize(sf::Vector2f(20, 20));
			blockShape.setOrigin(blockShape.getSize().x / 2, blockShape.getSize().y / 2);

			blockShape.setPosition(blocks.at(i)->getPosition().x * 20,
								   blocks.at(i)->getPosition().y * 20);

			blockShape.setFillColor(sf::Color(
				blocks.at(i)->getID().color.x,
				blocks.at(i)->getID().color.y,
				blocks.at(i)->getID().color.z
			));



			window->draw(blockShape);
		}

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
			
			topLeft = sf::Vector2f(entityShape.getPosition().x - (entityShape.getSize().x * 1.5),
								   entityShape.getPosition().y - (entityShape.getSize().y * 1.5));
			topRight = sf::Vector2f(entityShape.getPosition().x + (entityShape.getSize().x * 1.5),
									entityShape.getPosition().y - (entityShape.getSize().y * 1.5));
			bottomLeft = sf::Vector2f(entityShape.getPosition().x - (entityShape.getSize().x * 1.5),
									  entityShape.getPosition().y + (entityShape.getSize().y * 1.5));
			bottomRight = sf::Vector2f(entityShape.getPosition().x + (entityShape.getSize().x * 1.5),
									   entityShape.getPosition().y + (entityShape.getSize().y * 1.5));

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

bool Game::willCollide(const Vec2i distance, Entity::DIRECTIONS moveNext)
{
	//1,1 left top
	//-1,-1 right bottom

	//Check if moving right
	if (distance.x == 1 && distance.y == 0 && moveNext == Entity::RIGHT)
		return true;
	//Check if moving left
	else if (distance.x == -1 && distance.y == 0 && moveNext == Entity::LEFT)
		return true;
	//Check if moving up
	else if (distance.x == 0 && distance.y == -1 && moveNext == Entity::UP)
		return true;
	//Check if moving down
	else if (distance.x == 0 && distance.y == 1 && moveNext == Entity::DOWN)
		return true;

	return false;
}
