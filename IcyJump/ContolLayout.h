#pragma once
#include<GL/glut.h>
#include "Block.h"

class ControlLayout {
public:
	void draw_layout_keyboard()
	{	
		float point1[2] = { 0,0 };
		float point2[2] = { 200,1080 };
		float color1[3] = { 56 / 255.0,46 / 255.0,28 / 255.0 };
		float color2[3] = { 186 / 255.0,163 / 255.0,120 / 255.0 };
		draw_side_block(point1, point2, color1, color2);
		float point3[2] = { 1720,0 };
		float point4[2] = { 1920,1080 };
		draw_side_block(point3, point4, color1, color2);

		draw_heading_keyboard();
		draw_control_heading(Block(400, 850, 1520, 950));
		draw_control_block(Block(400, 750, 1520, 825), "MOVE LEFT", "LEFT-ARROW", "A");
		draw_control_block(Block(400, 650, 1520, 725), "MOVE RIGHT", "RIGHT-ARROW", "D");
		draw_control_block(Block(400, 550, 1520, 625), "JUMP", "UP-ARROW", "W");
		draw_control_block(Block(400, 450, 1520, 525), "BRAKE", "DOWN-ARROW", "S               SPACE");
		draw_control_block(Block(400, 350, 1520, 425), "ACCEPT", "ENTER", "");
		draw_control_block(Block(400, 250, 1520, 325), "BACK", "ESC", "");
		draw_control_block(Block(400, 150, 1520, 225), "QUIT", "Q", "");
	}

	void draw_layout_controller()
	{
		float point1[2] = { 0,0 };
		float point2[2] = { 200,1080 };
		float color1[3] = { 56 / 255.0,46 / 255.0,28 / 255.0 };
		float color2[3] = { 186 / 255.0,163 / 255.0,120 / 255.0 };

		draw_side_block(point1, point2, color1, color2);

		float point3[2] = { 1720,0 };
		float point4[2] = { 1920,1080 };
		draw_side_block(point3, point4, color1, color2);

		draw_heading_controller();
		draw_control_heading(Block(400, 850, 1520, 950));
		draw_control_block(Block(400, 750, 1520, 825), "MOVE LEFT", "LS LEFT", "");
		draw_control_block(Block(400, 650, 1520, 725), "MOVE RIGHT", "LS RIGHT", "");
		draw_control_block(Block(400, 550, 1520, 625), "JUMP", "RT", "");
		draw_control_block(Block(400, 450, 1520, 525), "BRAKE", "LT", "");
		draw_control_block(Block(400, 350, 1520, 425), "ACCEPT", "A BUTTON", "");
		draw_control_block(Block(400, 250, 1520, 325), "BACK", "B BUTTON", "");
		draw_control_block(Block(400, 150, 1520, 225), "QUIT", "X BUTTON", "");
	}

	private:

	void draw_control_block(Block block, char action[], char primary[], char alternate[])
	{
		glColor3f(233 / 255.0, 229 / 255.0, 129 / 255.0);
		glRectf(block.x1, block.y1, block.x2, block.y2);
		glColor3f(0, 0, 0);
		glLineWidth(4);
		glBegin(GL_LINE_LOOP);
		glVertex2f(block.x1, block.y1);
		glVertex2f(block.x1, block.y2);
		glVertex2f(block.x2, block.y2);
		glVertex2f(block.x2, block.y1);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(block.xm, block.y1);
		glVertex2f(block.xm, block.y2);
		glEnd();

		glRasterPos2f(block.x1 + 50, block.ym - 9);
		for (int i = 0; i < strlen(action); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, action[i]);
		glRasterPos2f(block.xm + 50, block.ym - 9);
		for (int i = 0; i < strlen(primary); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, primary[i]);
		glRasterPos2f(block.xm + 300, block.ym - 9);
		for (int i = 0; i < strlen(alternate); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, alternate[i]);
	}

	void draw_control_heading(Block block)
	{
		char action[] = "ACTION";
		char primary[] = "PRIMARY";
		char alternate[] = "ALTERNATE";
		glColor3f(0, 0, 0);
		glRasterPos2f(block.x1 + 50, block.y1);
		for (int i = 0; i < strlen(action); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, action[i]);
		glRasterPos2f(block.xm + 50, block.y1);
		for (int i = 0; i < strlen(primary); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, primary[i]);
		glRasterPos2f(block.xm + 300, block.y1);
		for (int i = 0; i < strlen(alternate); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, alternate[i]);
	}

	void draw_heading_keyboard()
	{
		float color[3] = { 0,0,0 };
		float color_background[3] = { 15 / 255.0,124 / 255.0,198 / 255.0 };
		glColor3fv(color_background);
		glRectf(200, 1000, 1160, 1080);
		glColor3fv(color);
		glLineWidth(4);
		glBegin(GL_LINE_LOOP);
		glVertex2f(200, 1000);
		glVertex2f(1720, 1000);
		glVertex2f(1720, 1078);
		glVertex2f(200, 1078);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(1160, 1000);
		glVertex2f(1160, 1078);
		glEnd();
		char str1[] = "KEYBOARD";
		glColor3f(1, 1, 1);
		glRasterPos2f(600, 1030);
		for (int i = 0; i < strlen(str1); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str1[i]);

		char str2[] = "CONTROLLER";
		glColor3f(0, 0, 0);
		glRasterPos2f(1350, 1030);
		for (int i = 0; i < strlen(str2); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str2[i]);
	}

	void draw_heading_controller()
	{
		float color[3] = { 0,0,0 };
		float color_background[3] = { 15 / 255.0,124 / 255.0,198 / 255.0 };
		glColor3fv(color_background);
		glRectf(760, 1000, 1720, 1080);
		glColor3fv(color);
		glLineWidth(4);
		glBegin(GL_LINE_LOOP);
		glVertex2f(200, 1000);
		glVertex2f(1720, 1000);
		glVertex2f(1720, 1078);
		glVertex2f(200, 1078);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(760, 1000);
		glVertex2f(760, 1078);
		glEnd();
		char str1[] = "KEYBOARD";
		glColor3f(0, 0, 0);
		glRasterPos2f(400, 1030);
		for (int i = 0; i < strlen(str1); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str1[i]);

		char str2[] = "CONTROLLER";
		glColor3f(1, 1, 1);
		glRasterPos2f(1150, 1030);
		for (int i = 0; i < strlen(str2); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str2[i]);
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
};
