#pragma once
#include<GL/glut.h>
#include "Block.h"

class ControlLayout {
	public:
		void draw_control_block(Block block, char str1[] ,char str2[],char str3[])
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

			glRasterPos2f(block.x1+50, block.ym-9);
			for (int i = 0; i < strlen(str1); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str1[i]);
			glRasterPos2f(block.xm +50, block.ym -9);
			for (int i = 0; i < strlen(str2); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str2[i]);
			glRasterPos2f(block.xm + 300, block.ym - 9);
			for (int i = 0; i < strlen(str3); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str3[i]);
		}

		void draw_heading(Block block, char str1[], char str2[],char str3[])
		{
			glColor3f(0, 0, 0);
			glRasterPos2f(block.x1 + 50, block.y1);
			for (int i = 0; i < strlen(str1); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str1[i]);
			glRasterPos2f(block.xm + 50, block.y1);
			for (int i = 0; i < strlen(str2); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str2[i]);
			glRasterPos2f(block.xm+300 , block.y1);
			for (int i = 0; i < strlen(str3); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str3[i]);
		}

		void draw_layout()
		{

			float point1[2] = { 0,0 };
			float point2[2] = { 200,1080 };
			float color1[3] = { 56 / 255.0,46 / 255.0,28 / 255.0 };
			float color2[3] = { 186 / 255.0,163 / 255.0,120 / 255.0 };

			draw_side_block(point1, point2, color1, color2);

			float point3[2] = { 1720,0 };
			float point4[2] = { 1920,1080 };
			draw_side_block(point3, point4, color1, color2);
			draw_heading(Block(400, 950, 1520,1050),"ACTION", "PRIMARY", "ALTERNATE");
			draw_control_block(Block(400, 800, 1520, 900),"MOVE LEFT" ,"LEFT-ARROW","A");
			draw_control_block(Block(400, 650, 1520, 750), "MOVE RIGHT", "RIGHT-ARROW","D");
			draw_control_block(Block(400, 500, 1520, 600), "JUMP", "UP-ARROW","W");
			draw_control_block(Block(400, 350, 1520, 450), "BRAKE", "DOWN-ARROW","S               SPACE");
			draw_control_block(Block(400, 200, 1520, 300), "BACK", "ESC","");
			draw_control_block(Block(400, 50, 1520, 150), "QUIT", "Q","");
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
