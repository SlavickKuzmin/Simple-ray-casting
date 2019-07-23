#pragma once

#include <string>
#include "Color.h"
#include "TextureAtlas.h"
#include "Sprite.h"

class LevelMap
{
public:
	LevelMap(int map_width, int map_height, TextureAtlas* atlas, TextureAtlas* monsters);
	~LevelMap();

	void SetLevelMap(const char* levelMap);

	const char* GetLevelMap();
	const RGBAColor GetElementColor();
	const int& GetMapWidth() const;
	const int& GetMapHeight() const;
	TextureAtlas* GetTextureAtlas() const;
	TextureAtlas* GetMonsterAtlas() const;
	const RGBAColor& GetColorForBlock(int i);
	std::vector<Sprite> sprites;
private:
	int width;
	int height;
	std::string levelMap;
	std::vector<RGBAColor> colors;
	TextureAtlas* atlas;
	TextureAtlas* monsters;
};

