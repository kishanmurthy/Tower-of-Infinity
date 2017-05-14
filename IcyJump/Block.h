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
	static int count;
	int blockNumber;
	
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
		blockNumber = count++;
	}
	Block(float x1, float y1, float x2, float y2,int blockNumber)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		xm = (x1 + x2) / 2;
		ym = (y1 + y2) / 2;
		this->blockNumber = blockNumber;
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
		xm = (x1 + x2) / 2;
	}
	void increment_y(float y)
	{
		y1 += y;
		y2 += y;
		ym = (y1 + y2) / 2;
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

	float getXdiff()
	{
		return x2 - x1;
	}
	float getYdiff()
	{
		return y2 - y1;
	}

	void setBlockNumber(int blockNumber)
	{
		this->blockNumber = blockNumber;
	}
};