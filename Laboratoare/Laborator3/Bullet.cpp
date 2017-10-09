#include "Bullet.h"


#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"

Bullet::Bullet()
{
	x = 0;
	y = 0;
}

Bullet::Bullet(int posx, int posy)
{
	x = posx;
	y = posy;
	velocity = 1;
}

Bullet::~Bullet()
{
}

void Bullet::move(int posx, int posy, int velo)
{
}

void Bullet::setRadius(int r)
{
	radius = r;
}

int Bullet::getter()
{
	return 0;
}

void Bullet::setter(int posx, int posy)
{
	
}


