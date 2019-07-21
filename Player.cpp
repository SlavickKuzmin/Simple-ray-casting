#include "Player.h"
#include <corecrt_math_defines.h>

Player::Player() : pos_x(0), pos_y(0)
{
	this->view_dir = 2 * M_PI / 360; // player view direction
}

void Player::SetPosition(float x, float y)
{
	this->pos_x = x;
	this->pos_y = y;
}

void Player::SetPositionX(float x)
{
	this->pos_x = x;
}

void Player::SetPositionY(float y)
{
	this->pos_y = y;
}

const float& Player::GetPositionX()
{
	return this->pos_x;
}

const float& Player::GetPositionY()
{
	return this->pos_y;
}

void Player::SetViewDir(float dir)
{
	this->view_dir = dir;
}

const float& Player::GetViewDir() const
{
	return this->view_dir;
}

RGBAColor Player::GetColor()
{
	return RGBAColor((byte)255, (byte)0, (byte)0);
}

Player::~Player()
{
}
