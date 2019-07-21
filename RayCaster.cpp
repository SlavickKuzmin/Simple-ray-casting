#include "RayCaster.h"
#include <corecrt_math_defines.h>

RayCaster::RayCaster(int render_width, int render_height, Viewport *l_view, Viewport *r_view) 
	: width(render_width), height(render_height), left_view(l_view), right_view(r_view)
{
	RGBAColor bacgroundColor((byte)255, (byte)255, (byte)255);
	this->fov = M_PI / 3.0;
	this->ray_color = RGBAColor((byte)0, (byte)0, (byte)255);
}

RayCaster::~RayCaster()
{
}

void RayCaster::SetLevelMap(LevelMap* _map)
{
	this->levelMap = _map;
	this->rect_w = this->left_view->GetWidth() / this->levelMap->GetMapWidth();
	this->rect_h = this->left_view->GetHeight() / this->levelMap->GetMapHeight();
}

void RayCaster::SetPlayer(Player* player)
{
	this->player = player;
}

Player* RayCaster::GetPlayer() const
{
	return this->player;
}

void RayCaster::Draw() const
{
	DrawLevelMap();

#pragma omp parallel for
	for (int i = 0; i < this->left_view->GetWidth(); i++) { // draw the visibility cone
		float angle = this->player->GetViewDir() - fov / 2 + fov * i / float(this->width);
		cast_ray(angle, i);
	}
}


const int& RayCaster::GetWidth() const
{
	return this->width;
}

const int& RayCaster::GetHeight() const
{
	return this->height;
}

Viewport* RayCaster::GetLeftViewport()
{
	return this->left_view;
}

Viewport* RayCaster::GetRightViewport()
{
	return this->right_view;
}

void RayCaster::DrawLevelMap() const
{
	for (int j = 0; j < this->levelMap->GetMapWidth(); j++) { // draw the map
		for (int i = 0; i < this->levelMap->GetMapHeight(); i++) {
			if (levelMap->GetLevelMap()[i + j * this->levelMap->GetMapWidth()] == ' ') continue; // skip empty spaces
			int rect_x = i * rect_w;
			int rect_y = j * rect_h;

			int index = levelMap->GetLevelMap()[i + j * this->levelMap->GetMapWidth()] - '0';
			Drawing::draw_rectangle(this->left_view,
				rect_x, rect_y, rect_w, rect_h, this->levelMap->GetTextureAtlas()->GetTexture()[index * this->levelMap->GetTextureAtlas()->GetTextureSize()]);
		}
	}

	Drawing::draw_rectangle(this->left_view, this->player->GetPositionX()*rect_w, this->player->GetPositionY()*rect_h,
		5, 5, this->player->GetColor());
}

void RayCaster::cast_ray(float angle, int& i) const
{
	for (float t = 0; t < 20; t += .05) {
		float cx = this->player->GetPositionX() + t * cos(angle);
		float cy = this->player->GetPositionY() + t * sin(angle);

		int pix_x = cx * rect_w;
		int pix_y = cy * rect_h;
		this->left_view->SetPixel(pix_x, pix_y, ray_color);

		int index = int(cx) + int(cy) * this->levelMap->GetMapWidth();
		if (this->levelMap->GetLevelMap()[index] != ' ')
		{ 
			float player_angle = this->GetPlayer()->GetViewDir();
			size_t column_height = this->right_view->GetHeight() / (t * cos(angle - player_angle));

			//Drawing::draw_rectangle(this->right_view,
			//	i, this->right_view->GetHeight() / 2 - column_height / 2,
			//	1, column_height, this->levelMap->GetTextureAtlas()->GetTexture()[index* this->levelMap->GetTextureAtlas()->GetTextureSize()]);
			
			float hitx = cx - floor(cx + .5); // hitx and hity contain (signed) fractional parts of cx and cy,
			float hity = cy - floor(cy + .5); // they vary between -0.5 and +0.5, and one of them is supposed to be very close to 0
			int x_texcoord = hitx * this->levelMap->GetTextureAtlas()->GetTextureSize();
			if (std::abs(hity) > std::abs(hitx)) { // we need to determine whether we hit a "vertical" or a "horizontal" wall (w.r.t the map)
				x_texcoord = hity * this->levelMap->GetTextureAtlas()->GetTextureSize();
			}
			if (x_texcoord < 0) 
				x_texcoord += this->levelMap->GetTextureAtlas()->GetTextureSize(); // do not forget x_texcoord can be negative, fix that
			int ind = this->levelMap->GetLevelMap()[index] - '0';
			std::vector<RGBAColor> column = this->levelMap->GetTextureAtlas()->GetColumn(ind, x_texcoord, column_height);
			pix_x = i;
			for (size_t j = 0; j < column_height; j++) {
				pix_y = j + this->right_view->GetHeight() / 2- column_height / 2;
				if (pix_y < 0 || pix_y >= (int)this->right_view->GetHeight()) continue;
				this->right_view->SetPixel(pix_x, pix_y, column[j]);
			}
			break;
		}
	}
}
