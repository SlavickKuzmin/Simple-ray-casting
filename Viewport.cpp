#include "Viewport.h"
#include "Screen.h"

void Viewport::SetPixel(int x, int y, const RGBAColor& color)
{
	int vx = x + x_offs;
	int vy = y + y_offs;
	// todo add out of range check
	this->scr->SetPixel(vx, vy, color);
}

int Viewport::GetWidth()
{
	return this->width;
}

int Viewport::GetHeight()
{
	return this->height;
}

void Viewport::ClearScreen()
{
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			this->scr->SetPixel(i, j, this->scr->GetBgColor());
		}
	}
}

void Viewport::ClearScreen(const RGBAColor& color)
{
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			this->scr->SetPixel(i, j, color);
		}
	}
}

Viewport::~Viewport()
{
}
