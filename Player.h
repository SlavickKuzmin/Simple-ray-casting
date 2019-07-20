#pragma once

#include "Color.h"

class Player
{
public:
	Player();
	void SetPosition(int x, int y);
	void SetPositionX(int x);
	void SetPositionY(int y);
	const int& GetPositionX();
	const int& GetPositionY();
	RGBAColor GetColor();
	~Player();
private:
	int pos_x;
	int pos_y;
};

