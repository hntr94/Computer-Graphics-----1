#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Bullet
{
public:
	Bullet();
	Bullet(int x, int y);
	~Bullet();
	void move(int posx, int posy, int velo);
	void setRadius(int r);
	int x, y;
	double angle;
	double velocity;
	int radius;

private:
	void move();
	int getter();
	void setter(int posx, int posy);







};