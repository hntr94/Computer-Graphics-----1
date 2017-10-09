#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Gift.h"

Gift::Gift()
{
}

Gift::Gift(int px, int py, int ptype, int pradius)
{
	x = px;
	y = py;
	type = ptype;
	radius = pradius;
}

Gift::~Gift()
{
}

void Gift::setRadius(int r)
{
}

void Gift::setColor(float rr, float gg, float bb)
{
	r = rr;
	g = gg;
	b = bb;
}
