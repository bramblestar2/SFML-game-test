#pragma once
#include <SFML/Graphics.hpp>
class CustomView
{
public:
	CustomView(sf::Vector2f, sf::Vector2f);
	CustomView();
	~CustomView();

	//Sets
	void moveTo(sf::Vector2f);
	void smoothTransition(bool a) { transition = a; }
	void setTransitionSpeed(float a) { transitionSpeed = a; }
	void setSize(sf::Vector2f);
	//Gets
	float getTransitionSpeed() const { return transitionSpeed; }
	sf::View getView() const { return view; }
	
	void update(const double _DT);

private:
	sf::View view;

	sf::Vector2f toPosition;
	bool transition;
	float transitionSpeed;
	float lerp(float, float, float);
};
