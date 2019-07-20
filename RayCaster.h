#pragma once

#include "Screen.h"
#include "Drawing.h"
#include "LevelMap.h"
#include "Player.h"

class RayCaster
{
public:
	RayCaster(int render_width, int render_height);
	~RayCaster();
	void SetLevelMap(LevelMap* map);
	void SetPlayer(Player* player);
	const Player& GetPlayer();
	void Draw() const;
	const Screen& GetScreen() const;
	const int& GetWidth() const;
	const int& GetHeight() const;
private:
	void DrawLevelMap() const;
	Screen* screen;
	LevelMap* levelMap;
	Player* player;
	int width;
	int height;
};

