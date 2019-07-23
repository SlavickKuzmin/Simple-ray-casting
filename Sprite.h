#pragma once


class Sprite
{
public:
	Sprite(float x, float y, int tex_id) : x(x), y(y), texture_id(tex_id) { };
	~Sprite() {};
	const float& GetX()
	{
		return x;
	}
	const float& GetY()
	{
		return y;
	}
	const int& GetTextureId()
	{
		return texture_id;
	}
private:
	float x;
	float y;
	int texture_id;
};

