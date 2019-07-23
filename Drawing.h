#pragma once

#include "Screen.h"
#include "Sprite.h"
#include "Player.h"
#include "TextureAtlas.h"
#include <algorithm>
#include "Viewport.h"

struct Drawing
{
	static void draw_rectangle(Viewport*scr, const int& x, const int& y,
		const int& w, const int& h, const RGBAColor& color);

	static void draw_sprite(Sprite& sprite, Viewport* src, Player* player, TextureAtlas* tex_sprites);
};

