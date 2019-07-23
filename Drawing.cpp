#include "Drawing.h"
#include <corecrt_math_defines.h>

void Drawing::draw_rectangle(Viewport* scr, const int& x, const int& y, const int& w, const int& h, const RGBAColor& color)
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

void  Drawing::draw_sprite(Sprite& sprite, Viewport* src, Player* player, TextureAtlas* tex_sprites)
{
	//// absolute direction from the player to the sprite (in radians)
	//float sprite_dir = atan2(sprite.GetY() - player->GetPositionY(), sprite.GetX() - player->GetPositionX());
	//// remove unnecessary periods from the relative direction
	//while (sprite_dir - player->GetViewDir() > M_PI) sprite_dir -= 2 * M_PI;
	//while (sprite_dir - player->GetViewDir() < -M_PI) sprite_dir += 2 * M_PI;

	//// distance from the player to the sprite
	//float sprite_dist = std::sqrt(pow(player->GetPositionX() - sprite.GetX(), 2) + pow(player->GetPositionY() - sprite.GetX(), 2));
	//size_t sprite_screen_size = std::min<int>(1024, static_cast<int>(512 / sprite_dist));
	//// do not forget the 3D view takes only a half of the framebuffer, thus fb.w/2 for the screen width
	//int h_offset = (sprite_dir - player->GetViewDir()) * (512) 
	//	/ (M_PI / 3.0) - (sprite_screen_size) / 2;
	//int v_offset = 512 / 2 - sprite_screen_size / 2;

	//for (size_t i = 0; i < sprite_screen_size; i++) {
	//	if (h_offset + int(i) < 0 || h_offset + i >= 512) continue;
	//	for (size_t j = 0; j < sprite_screen_size; j++) {
	//		if (v_offset + int(j) < 0 || v_offset + j >= 512) continue;
	//		src->SetPixel(h_offset + i, v_offset + j, RGBAColor((byte)0, (byte)0, (byte)0));
	//	}
	//}
}