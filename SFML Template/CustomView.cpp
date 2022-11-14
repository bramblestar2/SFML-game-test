#include "CustomView.h"

CustomView::CustomView(sf::Vector2f center, sf::Vector2f size)
{
	view = sf::View(center, size);

	toPosition = center;
	transition = true;
	transitionSpeed = 0.5f;
}

CustomView::CustomView()
{
	view = sf::View(sf::FloatRect(0, 0, 100, 100));
	transitionSpeed = 0.5f;
	transition = true;
}

CustomView::~CustomView()
{
}

void CustomView::update(const double _DT)
{

	if (transition)
		view.setCenter(lerp(view.getCenter().x, toPosition.x, transitionSpeed),
			lerp(view.getCenter().y, toPosition.y, transitionSpeed));
	else
		view.setCenter(toPosition);
}

void CustomView::moveTo(sf::Vector2f a)
{
	toPosition = a;
}

void CustomView::setSize(sf::Vector2f a)
{
	view.setSize(a);
}

float CustomView::lerp(float a, float b, float t)
{
	return a + t * (b - a);
}
