#include "Game.h"
#include <math.h>
#include <time.h>
//c++20
#include <filesystem>

namespace fs = std::filesystem;

Game::Game()
{
	srand(time(NULL));

	window = nullptr;

	entities.push_back(new Player());
	//((Player*)entities.at(0))->setMovementKeys(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);
	selectedBlockID = 0;

	for (int i = -10; i < 10; i++)
	{
		for (int k = -10; k < 10; k++)
		{
			float something = cos(i*k*rand()) + sin(k-i*rand());
			if (something > 1.f)
				selectedBlockID = 0;
			else
				selectedBlockID = 1;

			if (selectedBlockID == 0)
				placeBlock(Vec2i(i, k));
			//else if (selectedBlockID == 1)
			//	placeBlock(Vec2i(i, k));
		}
	}
	selectedBlockID = 0;

	chunkLoader();
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
		if (window->hasFocus())
		{
			camera.update(_DT);
			window->setView(camera.getView());

			for (int i = 0; i < entities.size(); i++)
			{
				entities.at(i)->update(_DT);
				handleActions(entities.at(i));

				bool canMove = true;
				for (int k = 0; k < blocks.size(); k++)
				{
					bool inDistanceOne = checkDistance(entities.at(i)->getPosition(), blocks.at(k)->getPosition(), 10.f);

					if (inDistanceOne)
					{
						bool inDistanceTwo = checkDistance(entities.at(i)->getPosition(), blocks.at(k)->getPosition(), 1.f);

						int xDistance = blocks.at(k)->getPosition().x - entities.at(i)->getPosition().x;
						int yDistance = blocks.at(k)->getPosition().y - entities.at(i)->getPosition().y;
						float distance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));

						//Brightness of block
						//Uses the distance from the player
						if (blocks.at(k)->getID().id == 0)
							blocks.at(k)->changeBrightness((1 / distance) * 100);
						else if (blocks.at(k)->getID().id == 1)
							blocks.at(k)->changeBrightness((1 / distance) * 30);

						if (inDistanceTwo)
						{
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
				placeBlock(point);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				destroyBlock(point);
			}
		}
	}
}

void Game::render()
{
	if (window != nullptr)
	{
		/// 
		///		Render blocks
		/// 
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

		/// 
		///		Render entities
		/// 
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

			/// 
			///		Draw where the entity is looking
			/// 

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

void Game::handleActions(Entity* entity)
{
	while (entity->getActionHandler()->poll_events())
	{
		ACTIONS event = entity->getActionHandler()->getEvent();
		
		if (event == ACTIONS::ENTERED_NEW_CHUNK)
		{
			Vec2i chunkPos = entity->getChunkPosition();
			std::cout << "Entity (Type: " << entity->getID().getType() << ") entered new chunk <"
					  << chunkPos.x << ", " << chunkPos.y << ">" << std::endl;
		}

		if (event == ACTIONS::ATTACK)
		{
			std::cout << "Entity (Type: " << entity->getID().getType() << ") has attacked" << std::endl;
		}
		if (event == ACTIONS::BREAK)
		{
			float breakAmount = 0.1f;

			Entity::DIRECTIONS directions = (Entity::DIRECTIONS)entity->getDirection();
			Vec2i pos = entity->getPosition();
			for (int i = 0; i < blocks.size(); i++)
			{
				Vec2i blockPos = blocks.at(i)->getPosition();
				if (directions == Entity::UP)
					if (pos.x == blockPos.x && pos.y - 1 == blockPos.y)
						blocks.at(i)->damage(breakAmount);
				else if (directions == Entity::DOWN)
					if (pos.x == blockPos.x && pos.y + 1 == blockPos.y)
						blocks.at(i)->damage(breakAmount);
				else if (directions == Entity::LEFT)
					if (pos.x - 1 == blockPos.x && pos.y == blockPos.y)
						blocks.at(i)->damage(breakAmount);
				else if (directions == Entity::RIGHT)
					if (pos.x + 1== blockPos.x && pos.y == blockPos.y)
						blocks.at(i)->damage(breakAmount);

				if (blocks.at(i)->isBroken())
					deleteBlock(i);
			}

			std::cout << "Entity (Type: " << entity->getID().getType() << ") is mining" << std::endl;
		}
		if (event == ACTIONS::PLACED_BLOCK)
		{
			Entity::DIRECTIONS directions = (Entity::DIRECTIONS)entity->getDirection();

			if (directions == Entity::UP)
				placeBlock(Vec2i(entity->getPosition().x, entity->getPosition().y-1));
			else if (directions == Entity::DOWN)
				placeBlock(Vec2i(entity->getPosition().x, entity->getPosition().y+1));
			else if (directions == Entity::LEFT)
				placeBlock(Vec2i(entity->getPosition().x-1, entity->getPosition().y));
			else if (directions == Entity::RIGHT)
				placeBlock(Vec2i(entity->getPosition().x+1, entity->getPosition().y));

			std::cout << "Entity (Type: " << entity->getID().getType() << ") placed a block" << std::endl;
		}
	}
}

bool Game::placeBlock(Vec2i position)
{
	bool placed = false;
	
	bool canPlace = true;

	for (int i = 0; i < blocks.size() && canPlace; i++)
	{
		canPlace = !(blocks.at(i)->getPosition() == position);
	}

	if (canPlace)
	{
		blocks.push_back(new Block(position));
		ID id = blocks.at(blocks.size() - 1)->getID();
		id.id = selectedBlockID;
		blocks.at(blocks.size() - 1)->setID(id);
		placed = true;
	}
	

	return placed;
}

bool Game::destroyBlock(Vec2i position)
{
	bool destroyed = false;
	for (int i = 0; i < blocks.size(); i++)
	{
		for (int i = 0; i < blocks.size(); i++)
		{
			if (blocks.at(i)->getPosition() == position)
			{
				delete blocks.at(i);
				blocks.erase(blocks.begin() + i);
				break;
			}
		}
	}

	return destroyed;
}

void Game::chunkLoader()
{
	std::string worldDir = fs::current_path().string() + "\\World\\";
	std::vector<int> players;
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities.at(i)->getID().getType() == "Player")
			players.push_back(i);
	}

	//fs::is_directory
	if (fs::is_directory(worldDir))
	{
		std::cout << "Directory exists" << std::endl;
		for (int i = 0; i < players.size(); i++)
		{
			Player* player = (Player*)entities.at(players.at(i));
			std::string chunk = std::to_string(player->getChunkPosition().x) + "," + 
								std::to_string(player->getChunkPosition().y);

			std::cout << chunk << std::endl;
		}

		
	}
	else
	{
		fs::create_directory(worldDir);
	}
}

void Game::loadChunk(Vec2i)
{
}

void Game::saveChunkData()
{
	
	//std::fstream saveData("", std::ios::app);
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

void Game::deleteBlock(int pos)
{
	delete blocks.at(pos);
	blocks.erase(blocks.begin() + pos);
}
