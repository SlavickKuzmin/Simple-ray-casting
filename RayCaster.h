#pragma once

#include "Screen.h"
#include "Drawing.h"
#include "LevelMap.h"
#include "Player.h"

class RayCaster
{
public:
	RayCaster(int render_width, int render_height, Viewport *l_view, Viewport *r_view);
	~RayCaster();
	void SetLevelMap(LevelMap* map);
	void SetPlayer(Player* player);
	Player* GetPlayer() const;
	void Draw() const;
	const int& GetWidth() const;
	const int& GetHeight() const;
	Viewport* GetLeftViewport();
	Viewport* GetRightViewport();
private:
	void DrawLevelMap() const;
	Viewport* left_view;
	Viewport* right_view;
	LevelMap* levelMap;
	Player* player;
	int width;
	int height;
	float fov;
	inline void cast_ray(float angle, int& i) const;
	int rect_w;
	int rect_h;
	RGBAColor ray_color;
};

