#include<stdio.h>
#include <GL/glut.h>
class MenuLayout {
	int selected_option = 0;

public:

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
		draw_title();
		draw_button(960, 540, "   PLAY  ");
		draw_button(960, 240, "CONTROLS");
		set_option_box();
	}



	int get_option(bool keys[])
	{
		set_option(keys);
		if (keys[4]) //enter key
		{
			return selected_option;
		}
		return -1;
	}
	private:

	void set_option(bool keys[])
	{
			if (keys[0])
			{
				selected_option = 0;
			}
			else if (keys[1])
			{
				selected_option = 1;
			}
			set_option_box();
	}
	void draw_button(float x, float y, char * name)
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

		glRasterPos2f(x - 50, y - 12);
		for (int i = 0; i < strlen(name); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, name[i]);
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

	void draw_title()
	{
		float color[3] = { 0,0,0 };
		float color_background[3] = { 15 / 255.0,124 / 255.0,198 / 255.0 };
		float color1[3] = { 56 / 255.0,46 / 255.0,28 / 255.0 };
		float color2[3] = { 80 / 255.0,60 / 255.0,40 / 255.0 };

		glColor3fv(color_background);
		glRectf(200, 800, 1720, 1080);
		glColor3fv(color);
		glLineWidth(4);
		glBegin(GL_LINE_LOOP);
		glVertex2f(200, 800);
		glVertex2f(200, 1078);
		glVertex2f(1720, 1078);
		glVertex2f(1720, 800);
		glEnd();

		char str1[] = "TOWER OF INFINITY";
		glColor3f(1, 1, 1);
		glRasterPos2f(830, 925);
		for (int i = 0; i < strlen(str1); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str1[i]);
	}
	void set_option_box()
	{
		glColor3f(1, 1, 1);
		glLineWidth(10);
		if (selected_option == 0)
		{
			glBegin(GL_LINE_LOOP);
			glVertex2f(960 - 190, 540 - 90);
			glVertex2f(960 - 190, 540 + 90);
			glVertex2f(960 + 190, 540 + 90);
			glVertex2f(960 + 190, 540 - 90);
			glEnd();
		}
		else if (selected_option==1)
		{
			glBegin(GL_LINE_LOOP);
			glVertex2f(960 - 190, 240 - 90);
			glVertex2f(960 - 190, 240 + 90);
			glVertex2f(960 + 190, 240 + 90);
			glVertex2f(960 + 190, 240 - 90);
			glEnd();
		}
	}
};