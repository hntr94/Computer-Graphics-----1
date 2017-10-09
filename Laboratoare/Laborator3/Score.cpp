#include "Score.h"

Score::Score()
{
	points = 0;
	lives = 3;
}

Score::Score(int lives, int points)
{
	points = 0;
	lives = 3;
}

Score::~Score()
{
}

void Score::decrement()
{
	lives = lives - 1;
}

int Score::getter()
{
	return 0;
}

void Score::setter(int posx, int posy)
{
}
