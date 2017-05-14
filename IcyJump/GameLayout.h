#pragma once
#include<stdio.h>
#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<cmath>
#include<GL/glut.h>
#include "Block.h"
using namespace std;
class GameLayout {
	public:
	//vector<Block> blockArray;
	list<Block> block;
	int blockPushed=-1;
	int blockPoped=-1;
	float collisionValue;
	int collisionAxis = 0;
	GameLayout()
	{
		block.push_back(Block(200, 50, 1720, 100,0)); 
		block.push_back(Block(200, 300, 1000, 350, 1));
		block.push_back(Block(500, 500, 1720, 550, 2));
		block.push_back(Block(200, 700, 800, 750, 3));
		block.push_back(Block(700, 900, 1720, 950 ,4 ));
		block.push_back(Block(200, 1100, 1400, 1150 ,5));
		block.push_back(Block(1000, 1300, 1720, 1350 ,6));
	
		blockPushed = 6;
		
	}
	void reset()
	{
		block.clear();
		block.push_back(Block(200, 50, 1720, 100, 0));
		block.push_back(Block(200, 300, 1000, 350, 1));
		block.push_back(Block(500, 500, 1720, 550, 2));
		block.push_back(Block(200, 700, 800, 750, 3));
		block.push_back(Block(700, 900, 1720, 950, 4));
		block.push_back(Block(200, 1100, 1400, 1150, 5));
		block.push_back(Block(1000, 1300, 1720, 1350, 6));
		blockPushed = 6;
		blockPoped = -1;

	}

	void generate_random_block_1()
	{
		float x_value= rand() % 1000 + 400;
		block.push_back(Block(200, 1500, x_value, 1550));
	}


	void generate_random_block_2()
	{
		float x_value = rand() % 1000 + 400;
		block.push_back(Block(x_value, 1500, 1720, 1550));
	}
	void updateBlocks()
	{
			if (!isVisible())
			{
				if (blockPoped % 2 == 0)
					generate_random_block_2();
				else
					generate_random_block_1();
				blockPushed++;
				block.back().setBlockNumber(blockPushed);
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
		glColor3f(0, 0, 0);
		glLineWidth(4);
		glBegin(GL_LINE_LOOP);
		glVertex2f(block.x2, block.y2);
		glVertex2f(block.x1, block.y2);
		glVertex2f(block.x1, block.y1);
		glVertex2f(block.x2, block.y1);
		glEnd();
		glBegin(GL_POLYGON);
			glColor3fv(color2);
			glVertex2f(block.x2, block.y2);
			glVertex2f(block.x1, block.y2);
			glColor3fv(color1);
			glVertex2f(block.x1, block.y1);
			glVertex2f(block.x2, block.y1);
			glEnd();
		
		if(block.blockNumber%10==0)
			displayNumbers(block);
		
	}
	void displayNumbers(Block &block)
	{
		glColor3f(233 / 255.0, 229 / 255.0, 129 / 255.0);
		glRectf(block.xm-15, block.ym-15, block.xm+20, block.ym+15);
		glColor3f(0, 0, 0);
		glLineWidth(4);
		glBegin(GL_LINE_LOOP);
		glVertex2f(block.xm-15, block.ym - 15);
		glVertex2f(block.xm - 15, block.ym +15);
		glVertex2f(block.xm +20, block.ym +15);
		glVertex2f(block.xm +20, block.ym - 15);
		glEnd();
		char str[5];
		itoa(block.blockNumber, str, 10);
		glColor3f(0, 0, 0);
		glRasterPos2f(block.xm-10, block.ym-10);

		for (int i = 0; i < strlen(str); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}

	void render_blocks()
	{
		float color1[3] = { 44/255.0,36 / 255.0,22 / 255.0 };
		float color2[3] = { 186 / 255.0,163 / 255.0,120 / 255.0 };
	
		for (list<Block>::iterator blockIterator = block.begin(); blockIterator != block.end(); blockIterator++)
		{
			draw_main_block(*blockIterator, color1, color2);
		}
		
	}

	void draw_layout()
	{
		float point1[2] = { 0,0 };
		float point2[2] = { 200,1080 };
		float color1[3] = { 56/255.0,46 / 255.0,28 / 255.0 };
		float color2[3] = { 186 /255.0,163 / 255.0,120 / 255.0 };

		draw_side_block(point1, point2, color1, color2);
		
		float point3[2] = { 1720,0 };
		float point4[2] = { 1920,1080 };
		draw_side_block(point3, point4, color1, color2);

		render_blocks();
		display_score();
	}

	void display_score()
	{
		glColor3f(233/255.0, 229/255.0, 129/255.0);
		glRectf(1750, 980, 1920, 1080);
		
		glColor3f(0, 0, 0);
		glLineWidth(5);
		glBegin(GL_LINE_LOOP);
			glVertex2f(1750, 1080);
			glVertex2f(1750, 980);
			glVertex2f(1920,980);
			glVertex2f(1920, 1080);
			
		glEnd();


		
		char score[] ="Score";
		glRasterPos2f(1810, 1050);
		for (int i = 0; i < strlen(score); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
		
		char str[5];
		if(blockPoped<=0)
			itoa(0, str, 10);
		else
			itoa(blockPoped*10, str, 10);
	
		glRasterPos2f(1820, 1000);

		for (int i = 0; i < strlen(str); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
	void draw_player(Block playerBlock)
	{
		glColor3f(233 / 255.0, 229 / 255.0, 129 / 255.0);
		glRectf(playerBlock.x1,playerBlock.y1, playerBlock.x2, playerBlock.y2);
		glColor3f(0, 0, 0);
		glLineWidth(2);
		glBegin(GL_LINE_STRIP);
		glVertex2f(playerBlock.x1, playerBlock.y1);
		glVertex2f(playerBlock.x1, playerBlock.y2);
		glVertex2f(playerBlock.x2, playerBlock.y2);
		glVertex2f(playerBlock.x2, playerBlock.y1);
		glVertex2f(playerBlock.x1, playerBlock.y1);
		glVertex2f((playerBlock.x1 + playerBlock.x2) / 2, playerBlock.y2);
		glVertex2f(playerBlock.x2, playerBlock.y1);
		glVertex2f(playerBlock.x2, playerBlock.y2);
		glVertex2f((playerBlock.x1 + playerBlock.x2) / 2, playerBlock.y1);
		glVertex2f(playerBlock.x1, playerBlock.y2);
		glEnd();
	}


	void draw_game_over()
	{
		glColor3f(233 / 255.0, 229 / 255.0, 129 / 255.0);
		glRectf(560, 340, 1260, 640);

		glColor3f(0, 0, 0);
		glLineWidth(5);
		glBegin(GL_LINE_LOOP);
		glVertex2f(560, 340);
		glVertex2f(560, 640);
		glVertex2f(1260, 640);
		glVertex2f(1260, 340);
		glEnd();



		char score[] = "GAME OVER!!!";
		glRasterPos2f(830, 480);
		for (int i = 0; i < strlen(score); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);

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
		

	}
	
	bool isVisible()
	{
		if (block.front().y2 < -10)
			return false;
		return true;
	}
	
};