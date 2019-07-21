#include "TextureAtlas.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureAtlas::TextureAtlas(const std::string filename)
{
	int nchannels = -1, w, h;
	unsigned char* pixmap = stbi_load(filename.c_str(), &w, &h, &nchannels, 0);
	if (!pixmap) {
		std::cerr << "Error: can not load the textures" << std::endl;
		abort();
	}

	if (4 != nchannels) {
		std::cerr << "Error: the texture must be a 32 bit image" << std::endl;
		stbi_image_free(pixmap);
		abort();
	}

	text_cnt = w / h;
	texture_size = w / text_cnt;
	if (w != h * int(text_cnt)) {
		std::cerr << "Error: the texture file must contain N square textures packed horizontally" << std::endl;
		stbi_image_free(pixmap);
		abort();
	}

	texture = std::vector<RGBAColor>(w * h);
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			RGBAColor color;
			color.r = pixmap[(i + j * w) * 4 + 0];
			color.g = pixmap[(i + j * w) * 4 + 1];
			color.b = pixmap[(i + j * w) * 4 + 2];
			color.a = pixmap[(i + j * w) * 4 + 3];
			texture[i + j * w] = color;
		}
	}
	stbi_image_free(pixmap);
}

size_t TextureAtlas::GetTextureSize() const
{
	return this->texture_size;
}

size_t TextureAtlas::GetTextureCnt() const
{
	return this->text_cnt;
}

const std::vector<RGBAColor>& TextureAtlas::GetTexture() const
{
	return this->texture;
}

std::vector<RGBAColor> TextureAtlas::GetColumn(int texid, int texcoord, int column_height)
{
	const size_t img_w = this->texture_size * this->text_cnt;
	const size_t img_h = this->texture_size;
	std::vector<RGBAColor> column(column_height);
	for (size_t y = 0; y < column_height; y++) {
		size_t pix_x = texid * this->texture_size + texcoord;
		size_t pix_y = (y * this->texture_size) / column_height;
		column[y] = this->texture[pix_x + pix_y * img_w];
	}
	return column;
}

TextureAtlas::~TextureAtlas()
{
}
