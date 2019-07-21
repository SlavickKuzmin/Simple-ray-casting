#pragma once

#include "Color.h"

#include <string>
#include <vector>
#include <iostream>

class TextureAtlas
{
public:
	TextureAtlas(const std::string filename);
	size_t GetTextureSize() const;
	size_t GetTextureCnt() const;
	const std::vector<RGBAColor>& GetTexture() const;
	std::vector<RGBAColor> GetColumn(int texid, int texcoord, int column_height);
	~TextureAtlas();
private:
	size_t texture_size;
	size_t text_cnt;
	std::vector<RGBAColor> texture;
};

