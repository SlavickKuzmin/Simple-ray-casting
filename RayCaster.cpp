#include "RayCaster.h"
#include <corecrt_math_defines.h>

RayCaster::RayCaster(int render_width, int render_height) : width(render_width), height(render_height)
{
	RGBAColor bacgroundColor((byte)255, (byte)255, (byte)255);
	this->screen = new Screen(width, height, bacgroundColor);
	this->fov = M_PI / 3.0;
	this->ray_color = RGBAColor((byte)0, (byte)0, (byte)255);
}

RayCaster::~RayCaster()
{
	delete this->screen;
}

void RayCaster::SetLevelMap(LevelMap* map)
{
	this->levelMap = map;
	this->rect_w = this->width / this->levelMap->GetMapWidth();
	this->rect_h = this->height / this->levelMap->GetMapHeight();
}

void RayCaster::SetPlayer(Player* player)
{
	this->player = player;
}

Player& RayCaster::GetPlayer()
{
	return *this->player;
}

void RayCaster::Draw() const
{
	DrawLevelMap();

	for (size_t i = 0; i < this->width; i++) { // draw the visibility cone
		float angle = this->player->GetViewDir() - fov / 2 + fov * i / float(this->width);
		cast_ray(angle);
	}
}

Screen& RayCaster::GetScreen() const
{
	return *this->screen;
}

const int& RayCaster::GetWidth() const
{
	return this->width;
}

const int& RayCaster::GetHeight() const
{
	return this->height;
}

void RayCaster::DrawLevelMap() const
{
	for (int j = 0; j < this->levelMap->GetMapWidth(); j++) { // draw the map
		for (int i = 0; i < this->levelMap->GetMapHeight(); i++) {
			if (levelMap->GetLevelMap()[i + j * this->levelMap->GetMapWidth()] == ' ') continue; // skip empty spaces
			int rect_x = i * rect_w;
			int rect_y = j * rect_h;
			Drawing::draw_rectangle(this->screen, rect_x, rect_y, rect_w, rect_h, this->levelMap->GetElementColor());
		}
	}

	Drawing::draw_rectangle(this->screen, this->player->GetPositionX()*rect_w, this->player->GetPositionY()*rect_h,
		5, 5, this->player->GetColor());
}

void RayCaster::cast_ray(float angle) const
{
	for (float t = 0; t < 20; t += .05) {
		float cx = this->player->GetPositionX() + t * cos(angle);
		float cy = this->player->GetPositionY() + t * sin(angle);
		if (this->levelMap->GetLevelMap()[int(cx) + int(cy) * this->levelMap->GetMapWidth()] != ' ') break;

		int pix_x = cx * rect_w;
		int pix_y = cy * rect_h;
		this->screen->SetPixel(pix_x, pix_y, ray_color);
	}
}
