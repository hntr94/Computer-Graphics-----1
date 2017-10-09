
#include "Player.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"

Player::Player()
{
	x = 0;
	y = 0;
	angle = 0;
	
}

Player::Player(int r)
{
	radius = r;
	x = 0;
	y = 0;
	angle = 0;
	invulnerable = false;
}

Player::~Player()
{

}

void Player::setRadius(int r)
{
	radius = r;
}

void Player::move()
{

}

int Player::getter()
{
	return 0;
}

void Player::setter(int posx, int posy)
{

}

