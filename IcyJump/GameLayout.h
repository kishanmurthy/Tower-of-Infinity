#pragma once
#include<iostream>
#include<vector>
#include<GL/glut.h>
#include "Block.h"
using namespace std;
class GameLayout {
	public:
	vector<Block> block;
	float collisionValue;
	int collisionAxis = 0;

	GameLayout()
	{
		block.push_back(Block(200, 50, 1720, 100));
		block.push_back(Block(200, 300, 800, 350));
		block.push_back(Block(800, 500, 1720, 550));
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
		for (vector<Block>::iterator blockIterator = block.begin(); blockIterator != block.end(); blockIterator++)
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

	bool checkVerticalCollision(const Block &playerBlock)
	{
		for (vector<Block>::iterator blockIterator = block.begin(); blockIterator != block.end(); blockIterator++)
		{
			if (playerBlock.x1 >= (*blockIterator).x1 && playerBlock.x2 <= (*blockIterator).x2)  
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
};