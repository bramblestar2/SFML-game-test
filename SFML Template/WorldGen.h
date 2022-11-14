#pragma once

class WorldGen
{
public:
	WorldGen(const int _X, const int _Y);
	WorldGen();
	~WorldGen();

	void setGenSeed(const unsigned int _SEED);
	void setGenSize(const int _X, const int _Y);
	void beginGen();

private:
	int genSeed;
	int worldSizeX, worldSizeY;


};

