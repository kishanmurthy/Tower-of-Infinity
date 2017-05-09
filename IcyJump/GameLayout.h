#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<GL/glut.h>
#include "Block.h"
using namespace std;
class GameLayout {
	public:
	vector<Block> blockArray;
	list<Block> block;
	int blockPushed=-1;
	int blockPoped=-1;
	float collisionValue;
	int collisionAxis = 0;

	GameLayout()
	{
		blockArray.push_back(Block(200, 50, 1720, 100));
		blockArray.push_back(Block(200, 300, 1000, 350));
		blockArray.push_back(Block(500, 500, 1720, 550));
		blockArray.push_back(Block(200, 700, 800, 750));
		blockArray.push_back(Block(700, 900, 1720, 950));
		blockArray.push_back(Block(200, 1100, 1500, 1150));
		blockArray.push_back(Block(1000, 1300, 1720, 1350));
		blockArray.push_back(Block(200, 1500, 1000, 1550));
		blockArray.push_back(Block(800, 1700, 1720, 1750));
		blockArray.push_back(Block(200, 1900, 1000, 1950));
		blockArray.push_back(Block(800, 2100, 1720, 2150));
		blockArray.push_back(Block(200, 2300, 1000, 2350));
		blockArray.push_back(Block(800, 2500, 1720, 2550));
		blockArray.push_back(Block(200, 2700, 1000, 2750));
		blockArray.push_back(Block(800, 2900, 1720, 2950));
		blockArray.push_back(Block(200, 3100, 1000, 3150));
		blockArray.push_back(Block(800, 3300, 1720, 3350));
		blockArray.push_back(Block(200, 3500, 1000, 3550));
		blockArray.push_back(Block(800, 3700, 1720, 3750));

		for (vector<Block>::iterator blockIterator = blockArray.begin(); blockPushed <6; blockIterator++ ,blockPushed++)
		{
			block.push_back(*blockIterator);
			
		}
		
	}

	void updateBlocks()
	{
		if(blockPushed < ( blockArray.capacity() - 1 ))
			if (!isVisible())
			{
				block.push_back(blockArray.at(++blockPushed));
				block.pop_front();
				blockPoped++;
			}
	}

	void draw_side_block(float *point1, float *point2, float *color1, float *color2)
	{

		
		glBegin(GL_POLYGON);
		glColor3fv(color1);
		glVertex2fv(point1);
		glVertex2f(point1[0], point2[1]);
		glColor3fv(color2);
		glVertex2f((point1[0] + point2[0]) / 2.0, point2[1]);
		glVertex2f((point1[0] + point2[0]) / 2.0, point1[1]);
		glEnd();
		glBegin(GL_POLYGON);
		glColor3fv(color2);
		glVertex2f((point1[0] + point2[0]) / 2.0, point1[1]);
		glVertex2f((point1[0] + point2[0]) / 2.0, point2[1]);
		glColor3fv(color1);
		glVertex2fv(point2);
		glVertex2f(point2[0], point1[1]);
		glEnd();

	}

	void draw_main_block(Block &block, float *color1, float *color2)
	{
		glColor3fv(color2);
		glRectf(block.x1, block.y1,block.x2,block.y2);

		float x1 = (block.x1 + (block.x2 - block.x1)*0.01);
		float y1 = (block.y1 + (block.y2 - block.y1)*0.1);
		float x2 = (block.x2 - (block.x2 - block.x1)*0.01);
		float y2 = (block.y2 - (block.y2 - block.y1)*0.1);

		glColor3fv(color1);
		glRectf(x1, y1, x2, y2);
	}

	void render_blocks()
	{
		float color1[3] = { 0.75, 0.75 ,0.75 };
		float color2[3] = { 1,1,1 };
		for (list<Block>::iterator blockIterator = block.begin(); blockIterator != block.end(); blockIterator++)
		{
			draw_main_block(*blockIterator, color1, color2);
		}
		
	}

	void draw_layout()
	{
		float point1[2] = { 0,0 };
		float point2[2] = { 200,1080 };
		float color1[3] = { 0.75, 0.75 ,0.75 };
		float color2[3] = { 1,1,1 };
		draw_side_block(point1, point2, color1, color2);
		
		float point3[2] = { 1720,0 };
		float point4[2] = { 1920,1080 };
		draw_side_block(point3, point4, color1, color2);

		render_blocks();

	}

	bool checkVerticalCollision(Block &playerBlock)
	{
		
		for (list<Block>::iterator blockIterator = block.begin(); blockIterator != block.end(); blockIterator++)
		{
			if (playerBlock.x1 > ( (*blockIterator).x1 - playerBlock.getXdiff()) && playerBlock.x2 < ((*blockIterator).x2 + playerBlock.getXdiff()))
				if (playerBlock.y1 <= (*blockIterator).y2 && playerBlock.y2 >= (*blockIterator).y1)
				{
					if (playerBlock.y1 > (*blockIterator).y1)
					{
						collisionValue = (*blockIterator).y2;
						collisionAxis = 2;
					}
					if (playerBlock.y2 < (*blockIterator).y2)
					{
						collisionValue = (*blockIterator).y1;
						collisionAxis = 1;
					}
					
					return true;
				}
		}
		return false;
	}
	bool checkHorizontalCollision(Block &playerBlock)
	{

		for (list<Block>::iterator blockIterator = block.begin(); blockIterator != block.end(); blockIterator++)
		{
			if (playerBlock.y1 > ((*blockIterator).y1 - playerBlock.getYdiff()) && playerBlock.y2 < ((*blockIterator).y2 + playerBlock.getYdiff()))
				if (playerBlock.x1 <= (*blockIterator).x2 && playerBlock.x2 >= (*blockIterator).x1)
				{
					if (playerBlock.x1 > (*blockIterator).x1)
					{
						collisionValue = (*blockIterator).x2;
						collisionAxis = 3;
					}
					if (playerBlock.x2 < (*blockIterator).x2)
					{
						collisionValue = (*blockIterator).x1;
						collisionAxis = 4;
					}

					return true;
				}
		}
		return false;
	}

	float getCollisionValue()
	{
		return collisionValue;
	}

	bool isCollisionAtTop()
	{
		if (collisionAxis == 1)
			return true;
		return false;
	}
	bool isCollisionAtBottom()
	{
		if (collisionAxis == 2)
			return true;
		return false;
	}

	bool isCollisionAtLeft()
	{
		if (collisionAxis == 3)
			return true;
		return false;
	}
	bool isCollisionAtRight()
	{
		if (collisionAxis == 4)
			return true;
		return false;
	}
	void decrementAllBlocks(float value)
	{
		for (list<Block>::iterator blockIterator = block.begin(); blockIterator != block.end(); blockIterator++)
		{
			blockIterator->increment_y(value*-1);
		}
		for (vector<Block>::iterator blockIterator = blockArray.begin(); blockIterator != blockArray.end(); blockIterator++)
		{
			blockIterator->increment_y(value*-1);
		}

	}
	
	bool isVisible()
	{
		if (block.front().y2 < -10)
			return false;
		return true;
	}

};