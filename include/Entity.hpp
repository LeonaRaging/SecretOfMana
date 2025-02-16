#pragma once

class Entity
{
public:
	Entity(int p_x, int p_y, int p_w, int p_h);
	int getX();
	int getY();
	int getW();
	int getH();
	void move(int x, int y);
private:
	int x, y, w, h;
};