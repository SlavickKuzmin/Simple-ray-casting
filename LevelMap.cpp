#include "LevelMap.h"

LevelMap::~LevelMap()
{
}

void LevelMap::SetLevelMap(const char* levelMap)
{
	this->levelMap = levelMap;
}

const char* LevelMap::GetLevelMap()
{
	return this->levelMap.c_str();
}

const RGBAColor LevelMap::GetElementColor()
{
	return RGBAColor((byte)0, (byte)0, (byte)0);
}

const int& LevelMap::GetMapWidth() const
{
	return this->width;
}

const int& LevelMap::GetMapHeight() const
{
	return this->height;
}
