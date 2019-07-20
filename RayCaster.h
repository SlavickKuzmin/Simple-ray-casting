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
	Player& GetPlayer();
	void Draw() const;
	Screen& GetScreen() const;
	const int& GetWidth() const;
	const int& GetHeight() const;
private:
	void DrawLevelMap() const;
	Screen* screen;
	LevelMap* levelMap;
	Player* player;
	int width;
	int height;
	float fov;
	inline void cast_ray(float angle) const;
	int rect_w;
	int rect_h;
	RGBAColor ray_color;
};

