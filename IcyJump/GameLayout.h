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
	list<Block> floors;
	int blockPushed;
	int blockPoped;
	int collisionAxis;
	float collisionValue;

public:
	GameLayout()
	{
		floors.push_back(Block(200, 50, 1720, 100, 0));
		floors.push_back(Block(200, 300, 1000, 350, 1));
		floors.push_back(Block(500, 500, 1720, 550, 2));
		floors.push_back(Block(200, 700, 800, 750, 3));
		floors.push_back(Block(700, 900, 1720, 950, 4));
		floors.push_back(Block(200, 1100, 1400, 1150, 5));
		floors.push_back(Block(1000, 1300, 1720, 1350, 6));

		blockPushed = 6;
	}
	bool checkHorizontalCollision(Block &playerBlock)
	{
		for (list<Block>::iterator blockIterator = floors.begin(); blockIterator != floors.end(); blockIterator++)
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

	bool checkVerticalCollision(Block &playerBlock)
	{
		for (list<Block>::iterator blockIterator = floors.begin(); blockIterator != floors.end(); blockIterator++)
		{
			if (playerBlock.x1 > ((*blockIterator).x1 - playerBlock.getXdiff()) && playerBlock.x2 < ((*blockIterator).x2 + playerBlock.getXdiff()))
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

	void decrementAllBlocks(float value)
	{
		for (list<Block>::iterator blockIterator = floors.begin(); blockIterator != floors.end(); blockIterator++)
		{
			blockIterator->increment_y(value*-1);
		}
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

	void draw_layout()
	{
		float point1[2] = { 0,0 };
		float point2[2] = { 200,1080 };
		float color1[3] = { 56 / 255.0,46 / 255.0,28 / 255.0 };
		float color2[3] = { 186 / 255.0,163 / 255.0,120 / 255.0 };

		draw_side_wall(point1, point2, color1, color2);

		float point3[2] = { 1720,0 };
		float point4[2] = { 1920,1080 };
		draw_side_wall(point3, point4, color1, color2);

		render_floors();
		draw_score();
	}

	void draw_player(Block playerBlock)
	{
		glColor3f(233 / 255.0, 229 / 255.0, 129 / 255.0);
		glRectf(playerBlock.x1, playerBlock.y1, playerBlock.x2, playerBlock.y2);
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
	float getCollisionValue()
	{
		return collisionValue;
	}

	int get_block_poped()
	{
		return blockPoped;
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

	bool isCollisionAtTop()
	{
		if (collisionAxis == 1)
			return true;
		return false;
	}

	void updateBlocks()
	{
		if (!is_floor_visible())
		{
			if (blockPoped % 2 == 0)
				generate_random_floor_right();
			else
				generate_random_floor_left();
			blockPushed++;
			floors.back().setBlockNumber(blockPushed);
			floors.pop_front();
			blockPoped++;
		}
	}
	void reset()
	{
		floors.clear();
		floors.push_back(Block(200, 50, 1720, 100, 0));
		floors.push_back(Block(200, 300, 1000, 350, 1));
		floors.push_back(Block(500, 500, 1720, 550, 2));
		floors.push_back(Block(200, 700, 800, 750, 3));
		floors.push_back(Block(700, 900, 1720, 950, 4));
		floors.push_back(Block(200, 1100, 1400, 1150, 5));
		floors.push_back(Block(1000, 1300, 1720, 1350, 6));
		blockPushed = 6;
		blockPoped = -1;
		collisionAxis = 0;
	}

private:

	void draw_floor_number(Block &block)
	{
		int no_of_digits = 0;
		int number = block.blockNumber;

		char str[5];
		itoa(block.blockNumber, str, 10);
		while (str[no_of_digits] != '\0')
		{
			no_of_digits++;
		}
		glColor3f(233 / 255.0, 229 / 255.0, 129 / 255.0);
		glRectf(block.xm - 7.5*no_of_digits, block.ym - 15, block.xm + 10 * no_of_digits, block.ym + 15);
		glColor3f(0, 0, 0);
		glLineWidth(4);
		glBegin(GL_LINE_LOOP);
		glVertex2f(block.xm - 7.5*no_of_digits, block.ym - 15);
		glVertex2f(block.xm - 7.5 * no_of_digits, block.ym + 15);
		glVertex2f(block.xm + 10 * no_of_digits, block.ym + 15);
		glVertex2f(block.xm + 10 * no_of_digits, block.ym - 15);
		glEnd();

		glColor3f(0, 0, 0);
		glRasterPos2f(block.xm - 4 * no_of_digits, block.ym - 8);

		for (int i = 0; i < strlen(str); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}

	void draw_floor_block(Block &block, float *color1, float *color2)
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

		if (block.blockNumber % 10 == 0)
			draw_floor_number(block);
	}

	void draw_score()
	{
		glColor3f(233 / 255.0, 229 / 255.0, 129 / 255.0);
		glRectf(1750, 980, 1920, 1080);

		glColor3f(0, 0, 0);
		glLineWidth(5);
		glBegin(GL_LINE_LOOP);
		glVertex2f(1750, 1080);
		glVertex2f(1750, 980);
		glVertex2f(1920, 980);
		glVertex2f(1920, 1080);

		glEnd();

		char score[] = "Score";
		glRasterPos2f(1810, 1050);
		for (int i = 0; i < strlen(score); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);

		char str[5];
		if (blockPoped <= 0)
			itoa(0, str, 10);
		else
			itoa(blockPoped * 10, str, 10);

		glRasterPos2f(1820, 1000);

		for (int i = 0; i < strlen(str); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}

	void draw_side_wall(float *point1, float *point2, float *color1, float *color2)
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
	void generate_random_floor_left()
	{
		float x_value = rand() % 1000 + 400;
		floors.push_back(Block(200, 1500, x_value, 1550));
	}
	void generate_random_floor_right()
	{
		float x_value = rand() % 1000 + 400;
		floors.push_back(Block(x_value, 1500, 1720, 1550));
	}
	void render_floors()
	{
		float color1[3] = { 44 / 255.0,36 / 255.0,22 / 255.0 };
		float color2[3] = { 186 / 255.0,163 / 255.0,120 / 255.0 };

		for (list<Block>::iterator blockIterator = floors.begin(); blockIterator != floors.end(); blockIterator++)
		{
			draw_floor_block(*blockIterator, color1, color2);
		}
	}

	bool is_floor_visible()
	{
		if (floors.front().y2 < -10)
			return false;
		return true;
	}
};