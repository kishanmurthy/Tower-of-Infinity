
#include<GL/glut.h>
#include<stdio.h>
#include<iostream>
using namespace std;
class KeyboardBuffer
{
public:
	static bool keys[7];
	static void keyboardDown(unsigned char c, int x, int y)
	{
		if (c == 'w' || c == 'W')
			keys[0] = true;
		else if (c == 's' || c == 'S'|| c == ' ')
			keys[1] = true;
		else if (c == 'a' || c == 'A')
			keys[2] = true;
		else if (c == 'd' || c == 'D')
			keys[3] = true;
		else if (c == 13)   //enter
			keys[4] = true;
		else if (c == 27)  //esc
			keys[5] = true;
		else if (c == 'q')
			exit(0);

	}
	static void keyboardUp(unsigned char c, int x, int y)
	{
		if (c == 'w' || c == 'W')
			keys[0] = false;
		else if (c == 's' || c == 'S' || c == ' ')
			keys[1] = false;
		else if (c == 'a' || c == 'A')
			keys[2] = false;
		else if (c == 'd' || c == 'D')
			keys[3] = false;
		else if (c == 13)
			keys[4] = false;
		else if (c == 27) 
			keys[5] = false;

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

	static void joystick(unsigned int b, int x, int y, int z)
	{
		keys[6] = true;
		if (z < -200)
		{
			keys[0] = true;
			keys[1] = false;
		}
		else if (z > 200)
		{
			keys[0] = false;
			keys[1] = true;
		}
		else
		{
			keys[0] = false;
			keys[1] = false;
		}


		if (x < -200)
		{
			keys[2] = true;
			keys[3] = false;
		}
		else if (x > 200)
		{
			keys[2] = false;
			keys[3] = true;
		}
		else
		{
			keys[2] = false;
			keys[3] = false;
		}

		if (b == GLUT_JOYSTICK_BUTTON_A)
			keys[4] = true;
		else
			keys[4] = false;

		if (b == GLUT_JOYSTICK_BUTTON_B)
			keys[5] = true;

		
		if (b == GLUT_JOYSTICK_BUTTON_C)
			exit(0);
			
	}

};