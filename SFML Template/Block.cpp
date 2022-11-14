#include "Block.h"

Block::Block(Vec2i pos, float brightness)
{
	id = ID("Block");
	id.id = 0;
	Vec3f color;
	HSVtoRGB(1,1,brightness, color.x, color.y, color.z);

	id.color = color;
	setPosition(pos);
}

Block::Block(Vec2i pos)
{
	id = ID("Block");
	id.color = Vec3f(10, 10, 10);
	id.id = 0;

	setPosition(pos);
}

Block::Block()
{
	id = ID("Block");
	id.color = Vec3f(150, 150, 150);
	id.id = 0;
}

Block::~Block()
{
}

void Block::update()
{
}

bool Block::isBroken()
{
	if (breakPercentage == 1.f)
	{
		id.color = Vec3f(70,70,70);
		return true;
	}

	return false;
}

void Block::changeBrightness(const float value)
{

	if (value < 0 || value > 100)
		id.color = Vec3f(10, 10, 10);
	else
	HSVtoRGB(1, 1, value, id.color.x, id.color.y, id.color.z);
}

void Block::HSVtoRGB(float H, float S, float V, float& R, float& G, float& B) {
	if (H > 360 || H < 0 || S>100 || S < 0 || V>100 || V < 0) {
		std::cout << "The givem HSV values are not in valid range" << std::endl;
		return;
	}
	float s = S / 100;
	float v = V / 100;
	float C = s * v;
	float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	float m = v - C;
	float r, g, b;
	if (H >= 0 && H < 60) {
		r = C, g = X, b = 0;
	}
	else if (H >= 60 && H < 120) {
		r = X, g = C, b = 0;
	}
	else if (H >= 120 && H < 180) {
		r = 0, g = C, b = X;
	}
	else if (H >= 180 && H < 240) {
		r = 0, g = X, b = C;
	}
	else if (H >= 240 && H < 300) {
		r = X, g = 0, b = C;
	}
	else {
		r = C, g = 0, b = X;
	}
	R = (r + m) * 255;
	G = (g + m) * 255;
	B = (b + m) * 255;
}