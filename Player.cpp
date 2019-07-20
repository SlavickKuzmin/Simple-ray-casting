#include "Player.h"

Player::Player() : pos_x(0), pos_y(0)
{
}

void Player::SetPosition(int x, int y)
{
	this->pos_x = x;
	this->pos_y = y;
}

void Player::SetPositionX(int x)
{
	this->pos_x = x;
}

void Player::SetPositionY(int y)
{
	this->pos_y = y;
}

const int& Player::GetPositionX()
{
	return this->pos_x;
}

const int& Player::GetPositionY()
{
	return this->pos_y;
}

RGBAColor Player::GetColor()
{
	return RGBAColor((byte)255, (byte)0, (byte)0);
}

Player::~Player()
{
}
