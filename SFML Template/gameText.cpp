#include "gameText.h"
#include <iostream>

GameText::GameText(sf::Font* font)
{
	this->font = font;

	size = 10;
	text.setFont(*font);
}

GameText::GameText()
{
	size = 0;
	font = nullptr;
}

GameText::~GameText()
{
}

void GameText::setSize(unsigned int size)
{
	this->size = size;
	text.setCharacterSize(size);
	text.setOrigin(text.getGlobalBounds().width / 2, 
				   text.getGlobalBounds().height / 2);
}

void GameText::setCenter(sf::Vector2f pos)
{
	text.setPosition(pos);
}

void GameText::setString(std::string str)
{
	text.setString(str);
	text.setOrigin(text.getGlobalBounds().width / 2,
		text.getGlobalBounds().height / 2);
}

void GameText::setColor(sf::Color color)
{
	text.setFillColor(color);
}

void GameText::render(sf::RenderWindow* window)
{
	window->draw(text);
}
