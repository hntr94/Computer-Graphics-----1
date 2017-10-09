#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Score
{
	public:
		Score();
		Score(int lives, int points);
		~Score();
		void decrement();
		int points;
		int lives;
		
	private:
		void move();
		int getter();
		void setter(int posx, int posy);







};