#pragma once
class Block
{
public:
	float x1;
	float y1;
	float x2;
	float y2;
	float xm;
	float ym;
	Block()
	{
		x1 = 0;
		y1 = 0;
		x2 = 0;
		y2 = 0;
		xm = 0;
		ym = 0;
	}
	Block(float x1, float y1, float x2, float y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		xm = (x1 + x2) / 2;
		ym = (y1 + y2) / 2;
	}
	void setAttrib(float x1, float y1, float x2, float y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		xm = (x1 + x2) / 2;
		ym = (y1 + y2) / 2;
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

	void setBlock(float xm, float ym,float size)
	{
		this->xm = xm;
		this->ym = ym;
		x1 = xm - size;
		y1 = ym - size;
		x2 = xm + size;
		y2 = ym + size;
	}
	
	void setX(float x1, float x2)
	{
		this->x1 = x1;
		this->x2 = x2;
		xm = (x1 + x2) / 2;
		
	}

	void setY(float y1, float y2)
{
		this->y1 = y1;
		this->y2 = y2;
		ym = (y1 + y2) / 2;

	}
};