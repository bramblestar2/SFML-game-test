#include "CustomView.h"

CustomView::CustomView(sf::Vector2f center, sf::Vector2f size) : sf::View(center, size)
{
	toPosition = center;
	transition = true;
	transitionSpeed = 0.5f;
}

CustomView::CustomView() : sf::View(sf::FloatRect(0,0,100,100))
{
}

CustomView::~CustomView()
{
}

void CustomView::update(const double _DT)
{
	this->setCenter(lerp(this->getCenter().x, toPosition.x, transitionSpeed),
					lerp(this->getCenter().y, toPosition.y, transitionSpeed));
}

void CustomView::moveTo(sf::Vector2f a)
{
	toPosition = a;
}

void CustomView::setSize(sf::Vector2f a)
{
	View::setSize(a);
}

float CustomView::lerp(float a, float b, float t)
{
	return a + t * (b - a);
}
