#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Player
{
public:
	Player();
	Player(int r);
	~Player();
	void setRadius(int r);
	int x, y;
	double angle;
	int radius;
	bool invulnerable;

private:
	void move();
	int getter();
	void setter(int posx, int posy);

	





};