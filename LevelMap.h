#pragma once

#include <string>
#include "Color.h"
#include "TextureAtlas.h"

class LevelMap
{
public:
	LevelMap(int map_width, int map_height, TextureAtlas* atlas);
	~LevelMap();

	void SetLevelMap(const char* levelMap);

	const char* GetLevelMap();
	const RGBAColor GetElementColor();
	const int& GetMapWidth() const;
	const int& GetMapHeight() const;
	TextureAtlas* GetTextureAtlas() const;
	const RGBAColor& GetColorForBlock(int i);
private:
	int width;
	int height;
	std::string levelMap;
	std::vector<RGBAColor> colors;
	TextureAtlas* atlas;
};

