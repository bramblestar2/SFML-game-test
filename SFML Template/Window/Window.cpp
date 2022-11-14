#include "Window.h"
#include <iostream>

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
	window->clear();

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
				window->close();
		}

		game.updateSFMLEvents(event, dt);
	}
}

void Window::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(400, 400), "Game Test", sf::Style::Default);
	window->setFramerateLimit(60);
}
