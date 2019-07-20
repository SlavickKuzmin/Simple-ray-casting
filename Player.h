#pragma once

#include "Color.h"

class Player
{
public:
	Player();
	void SetPosition(float x, float y);
	void SetPositionX(float x);
	void SetPositionY(float y);
	const float& GetPositionX();
	const float& GetPositionY();
	void SetViewDir(float dir);
	const float& GetViewDir();
	RGBAColor GetColor();
	~Player();
private:
	float pos_x;
	float pos_y;
	float view_dir;
};

