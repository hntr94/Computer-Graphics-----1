#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Enemy
{
public:
	Enemy();
	Enemy(int init_x, int init_y, int typeOf, int velo, float scale);
	Enemy(int x, int y);
	~Enemy();
	void setColor(float r, float g, float b);
	void setScale(float s);
	void setVelocity(int v);
	void setLife(int l);
	void setRadius(int r);
	int x, y, velocity, radius;
	double angle;
	int type, lives;
	float red, green, blue, scale;
	bool gotHit;

private:
	void move();
	int getter();
	void setter(int posx, int posy);

	







};