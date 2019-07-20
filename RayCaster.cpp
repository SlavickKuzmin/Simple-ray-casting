#include "RayCaster.h"

RayCaster::RayCaster(int render_width, int render_height) : width(render_width), height(render_height)
{
	RGBAColor bacgroundColor((byte)255, (byte)255, (byte)255);
	this->screen = new Screen(width, height, bacgroundColor);
}

RayCaster::~RayCaster()
{
	delete this->screen;
}

void RayCaster::SetLevelMap(LevelMap* map)
{
	this->levelMap = map;
}

void RayCaster::SetPlayer(Player* player)
{
	this->player = player;
}

const Player& RayCaster::GetPlayer()
{
	return *this->player;
}

void RayCaster::Draw() const
{
	DrawLevelMap();
}

const Screen& RayCaster::GetScreen() const
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
	const int rect_w = this->width / this->levelMap->GetMapWidth();
	const int rect_h = this->height / this->levelMap->GetMapHeight();
	for (int j = 0; j < this->levelMap->GetMapWidth(); j++) { // draw the map
		for (int i = 0; i < this->levelMap->GetMapHeight(); i++) {
			if (levelMap->GetLevelMap()[i + j * this->levelMap->GetMapWidth()] == ' ') continue; // skip empty spaces
			int rect_x = i * rect_w;
			int rect_y = j * rect_h;
			Drawing::draw_rectangle(this->screen, rect_x, rect_y, rect_w, rect_h, this->levelMap->GetElementColor());
		}
	}

	Drawing::draw_rectangle(this->screen, this->player->GetPositionX(), this->player->GetPositionY(),
		5, 5, this->player->GetColor());
}
