#include "Drawing.h"

void Drawing::draw_rectangle(Screen* scr, const int& x, const int& y, const int& w, const int& h, const RGBAColor& color)
{
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			int cx = x + i;
			int cy = y + j;
			scr->SetPixel(cx, cy, color);
		}
	}
}
