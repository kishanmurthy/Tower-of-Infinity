#pragma once
class Block
{
public:
	float x1;
	float y1;
	float x2;
	float y2;

	Block()
	{
		x1 = 0;
		y1 = 0;
		x2 = 0;
		y2 = 0;
	}
	Block(float x1, float y1, float x2, float y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
	void setAttrib(float x1, float y1, float x2, float y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
	void increment_x(float x)
	{
		x1 += x;
		x2 += x;
	}
	void increment_y(float y)
	{
		y1 += y;
		y2 += y;
	}
};