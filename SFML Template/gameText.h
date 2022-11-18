#pragma once
#include <SFML/Graphics.hpp>
class GameText
{
public:
	GameText(sf::Font*);
	GameText();
	~GameText();

	void setSize(unsigned int);
	void setCenter(sf::Vector2f);
	void setString(std::string);
	void setColor(sf::Color);
	std::string getString() const { return text.getString(); }

	void render(sf::RenderWindow* window);
private:
	int size;
	sf::Font* font;
	sf::Text text;
};

