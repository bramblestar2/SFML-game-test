#include "WorldGen.h"

WorldGen::WorldGen(const int _X, const int _Y)
{
	genSeed = 0;
	worldSizeX = _X;
	worldSizeY = _Y;
}

WorldGen::WorldGen()
{
	genSeed = 0;
	worldSizeX = 0;
	worldSizeY = 0;
}

WorldGen::~WorldGen()
{
}

void WorldGen::setGenSeed(const unsigned int _SEED)
{
	genSeed = _SEED;
}

void WorldGen::setGenSize(const int _X, const int _Y)
{
	worldSizeX = _X;
	worldSizeY = _Y;
}

void WorldGen::beginGen()
{
}
