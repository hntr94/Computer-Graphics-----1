#pragma once
class Gift
{
public:
	Gift();
	Gift(int x, int y, int type, int radius);
	~Gift();
	//void move(int posx, int posy, int velo);
	void setRadius(int r);
	void setColor(float r, float g, float b);
	int x, y;
	//double angle;
	float r, g, b;
	int radius;
	int type;
private:
	void move();
	int getter();
	void setter(int posx, int posy);







};