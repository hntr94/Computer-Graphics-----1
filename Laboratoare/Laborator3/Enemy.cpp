#include "Enemy.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"

Enemy::Enemy()
{
	x = 0;
	y = 0;
	angle = 0;
}

Enemy::Enemy(int init_x, int init_y, int typeOf, int velo, float sc)
{
	x = init_x;
	y = init_y;
	velocity = velo;
	type = typeOf;
	scale = sc;
}

Enemy::Enemy(int x, int y)
{
}

Enemy::~Enemy()
{

}

void Enemy::move()
{

}

int Enemy::getter()
{
	return 0;
}

void Enemy::setter(int posx, int posy)
{

}

void Enemy::setColor(float r, float g, float b) {
	red = r;
	green = g;
	blue = b;
}

void Enemy::setScale(float s) {
	scale = s;
}

void Enemy::setVelocity(int v) {
	velocity = v;
}

void Enemy::setLife(int l) {
	lives = l;
}

void Enemy::setRadius(int r)
{
	radius = r;
}
