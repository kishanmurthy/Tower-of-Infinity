#pragma once
#include<GL/glut.h>
#include<stdio.h>
class KeyboardBuffer
{
public:
	static bool keys[6];
	static void keyboardDown(unsigned char c, int x, int y)
	{
		if (c == 'w')
			keys[0] = true;
		else if (c == 's' || c == ' ')
			keys[1] = true;
		else if (c == 'a')
			keys[2] = true;
		else if (c == 'd')
			keys[3] = true;
		else if (c == 13)
			keys[4] = true;
		else if (c == 27)
			keys[5] == true;
		else if (c == 'q')
			exit(0);
	}
	static void keyboardUp(unsigned char c, int x, int y)
	{
		if (c == 'w')
			keys[0] = false;
		else if (c == 's' || c == ' ')
			keys[1] = false;
		else if (c == 'a')
			keys[2] = false;
		else if (c == 'd')
			keys[3] = false;
		else if (c == 13)
			keys[4] = true;
		else if (c == 27)
			keys[5] == true;
	}

	static void specialDown(int c, int x, int y)
	{
		if (c == GLUT_KEY_UP)
			keys[0] = true;
		else if (c == GLUT_KEY_DOWN)
			keys[1] = true;
		else if (c == GLUT_KEY_LEFT)
			keys[2] = true;
		else if (c == GLUT_KEY_RIGHT)
			keys[3] = true;
	


	}
	static void specialUp(int c, int x, int y)
	{
		if (c == GLUT_KEY_UP)
			keys[0] = false;
		else if (c == GLUT_KEY_DOWN)
			keys[1] = false;
		else if (c == GLUT_KEY_LEFT)
			keys[2] = false;
		else if (c == GLUT_KEY_RIGHT)
			keys[3] = false;

	}
};