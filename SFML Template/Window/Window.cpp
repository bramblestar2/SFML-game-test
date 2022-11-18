#include "Window.h"
#include <iostream>

#include "../gameText.h"

Window::Window()
{
	initWindow();
	game.setWindowPtr(window);
}

Window::~Window()
{
	delete window;
}

void Window::run()
{
	while (window->isOpen())
	{
		update();
		updateDt();
		updateSFMLEvents();
		render();
	}
}

void Window::render()
{
	window->clear(sf::Color(10,10,10));

	game.render();

	window->display();
}

void Window::update()
{
	game.update(dt);
}

void Window::updateDt()
{
	dt = dtClock.restart().asSeconds();
}

void Window::updateSFMLEvents()
{
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				menu();
		}

		game.updateSFMLEvents(event, dt);
	}
}

void Window::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(600, 400), "Game Test", sf::Style::Default);
	window->setFramerateLimit(60);
}

void Window::menu()
{
	bool exitMenu = false;
	sf::Texture ss;
	ss.create(window->getSize().x, window->getSize().y);
	ss.update(*window);

	sf::RectangleShape ssShape(sf::Vector2f(window->getSize()));
	ssShape.setTexture(&ss);

	sf::View currentView;
	currentView.setSize(sf::Vector2f(window->getSize()));
	currentView.setCenter(window->getSize().x - (window->getSize().x/2),
						  window->getSize().y - (window->getSize().y/2));
	window->setView(currentView);


	sf::RectangleShape dimBackground;
	dimBackground.setSize(ssShape.getSize());
	dimBackground.setFillColor(sf::Color(0, 0, 0, 100));

	sf::Font font;
	font.loadFromFile("Fonts/opFont.ttf");

	GameText title(&font), exit(&font), resume(&font);
	title.setString("Title");
	exit.setString("Exit Game");
	resume.setString("Resume Game");

	title.setSize(45);
	exit.setSize(30);
	resume.setSize(30);

	title.setCenter(sf::Vector2f(window->getSize().x/2,
								 window->getSize().y/5));
	resume.setCenter(sf::Vector2f(window->getSize().x / 2,
								  window->getSize().y / 2.5));
	exit.setCenter(sf::Vector2f(window->getSize().x / 2,
								  window->getSize().y / 2));

	while (window->isOpen() && !exitMenu)
	{
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					exitMenu = true;
			}
		}

		window->clear();

		window->draw(ssShape);
		window->draw(dimBackground);

		title.render(window);
		exit.render(window);
		resume.render(window);

		window->display();
	}
}
