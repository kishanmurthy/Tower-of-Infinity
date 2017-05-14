#pragma once
#include <GL/glut.h>
class MenuLayout {
public:
	void draw_game_logo()
	{
		//glColor3f()
		//glBegin(GL_POLYGON)
			
	}

	void draw_button(float x ,float y,char * str)
	{
		glColor3f(233 / 255.0, 229 / 255.0, 129 / 255.0);
		glRectf(x - 200, y - 100, x + 200, y + 100);
		glColor3f(0, 0, 0);
		glLineWidth(4);
		glBegin(GL_LINE_LOOP);
		glVertex2f(x - 200, y - 100);
		glVertex2f(x - 200, y + 100);
		glVertex2f(x + 200, y + 100);
		glVertex2f(x + 200, y - 100);
		glEnd();


		glRasterPos2f(x-30, y-12);
		for (int i = 0; i < strlen(str); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
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
		draw_game_logo();
		draw_button(960,540,"PLAY");
		draw_button(960, 240, "SETTINGS");

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