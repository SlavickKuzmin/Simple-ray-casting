#pragma once

#include <string>
#include "Color.h"

class LevelMap
{
public:
	LevelMap(int map_width, int map_height) : width(map_width), height(map_height) {};
	~LevelMap();

	void SetLevelMap(const char* levelMap);

	const char* GetLevelMap();
	const RGBAColor GetElementColor();
	const int& GetMapWidth() const;
	const int& GetMapHeight() const;
private:
	int width;
	int height;
	std::string levelMap;
};

