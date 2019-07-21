#include "LevelMap.h"

LevelMap::LevelMap(int map_width, int map_height, TextureAtlas *atlas) : width(map_width), height(map_height), atlas(atlas)
{
	const size_t ncolors = 5;
	colors.reserve(ncolors);
	for (size_t i = 0; i < ncolors; i++) {
		colors.push_back(RGBAColor((byte)(rand() % 255), (byte)(rand() % 255), (byte)(rand() % 255)));
	}
}

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

TextureAtlas* LevelMap::GetTextureAtlas() const
{
	return this->atlas;
}

const RGBAColor& LevelMap::GetColorForBlock(int i)
{
	return this->colors[i];
}
