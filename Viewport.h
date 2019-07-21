#pragma once

#include "Color.h"
class Screen;

class Viewport
{
public:
	Viewport(Screen* screen, int x, int y, int width, int height)
	{
		this->scr = screen;
		this->x_offs = x;
		this->y_offs = y;
		this->width = width;
		this->height = height;
	}

	void SetPixel(int x, int y, const RGBAColor& color);
	int GetWidth();
    int GetHeight();
	void ClearScreen();
	void ClearScreen(const RGBAColor& color);
	~Viewport();
private:
	Screen* scr;
	int x_offs;
	int y_offs;
	int width;
	int height;
};

