#pragma once

#include "Color.h"
#include "Viewport.h"

class Screen
{
public:
	// Default constructor
	// Default color = black
	Screen(int w, int h);
	Screen(int width, int height, const RGBAColor& fillColor);
	~Screen();
	void SetPixel(int x, int y, const RGBAColor& color) const;
	const int& GetWidth() const;
	const int& GetHeight() const;
	RGBAColor* GetPixels();
	const RGBAColor& GetBgColor();
	void ClearScreen();
private:
	int width;
	int height;
	RGBAColor* pixels;
	RGBAColor bgColor;
};

