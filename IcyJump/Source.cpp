#include<GL/glut.h>
#include<iostream>
#include<stdio.h>
#include "Player.h"
using namespace std;
#define FPS 60

bool keys[4] = { false };
Player player;

void render()
{
	glClearColor(0,0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0);
	glRectf(player.v[0], player.v[1], player.v[0]+50, player.v[1]+50);
	glFlush();
}

void keyboardDown(unsigned char c,int x,int y)
{
	if (c == 'w')
		keys[0] = true;
	else if (c == 's')
		keys[1] = true;
	else if (c == 'a')
		keys[2] = true;
	else if (c == 'd')
		keys[3] = true;
	


}
void keyboardUp(unsigned char c, int x, int y)
{
	if (c == 'w')
		keys[0] = false;
	else if (c == 's')
		keys[1] = false;
	else if (c == 'a')
		keys[2] = false;
	else if (c == 'd')
		keys[3] = false;

}

void specialDown(int c, int x, int y)
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
void specialUp(int c, int x, int y)
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

void timmer(int x)
{
	if (keys[0])
	{
		
		if (player.canJump)
		{
			player.acceleration_vertical = 100000;
			
		}
		else
		{
			player.acceleration_vertical = -5000;
		}
		
	}
	else
	{
		player.acceleration_vertical = -7500;
		
	}
	if (keys[2] && player.canJump)
	{
		player.acceleration_horizontal = -8000;
	}
	else if (keys[3] && player.canJump)
		player.acceleration_horizontal = 8000;
	else
	{
		if (player.jumpFinish)
		{
			if (player.initial_velocity_horizontal > 700 && player.canJump)
				player.acceleration_horizontal = -60000;
			else if (player.initial_velocity_horizontal < -700 && player.canJump)
				player.acceleration_horizontal = 60000;
			else if (player.canJump)
			{
				player.initial_velocity_horizontal = 0;
				player.acceleration_horizontal = 0;
			}
			player.jumpFinish = false;
		}
		else
		{
			if (player.initial_velocity_horizontal > 100 && player.canJump)
				player.acceleration_horizontal = -2000;
			else if (player.initial_velocity_horizontal < -100 && player.canJump)
				player.acceleration_horizontal = 2000;
			else if (player.canJump)
			{
				player.initial_velocity_horizontal = 0;
				player.acceleration_horizontal = 0;
			}
		}
	}
	player.compute_velocity();
	player.compute_displacement();
	player.move_object();

	if (player.acceleration_vertical == 100000)
	{
		player.canJump = false;
		player.acceleration_horizontal = 0;

	}
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timmer, 60);

}
void reshape(int w,int h)
{
	float aspectRatio = 16.0 / 9.0;
	float aspectRatioDiff= float(w) / float(h) - aspectRatio;
	float aspectRatioChange = aspectRatioDiff / aspectRatio;
	if (aspectRatioChange>0)
	{
		glViewport((w-aspectRatio*h)/2, 0, aspectRatio*h, h);
	}
	else if (aspectRatioChange < 0)
	{
		glViewport(0, (h - (1 / aspectRatio)*w)/2, w, (1 / aspectRatio)*w);
	}
	glutPostRedisplay();
}
void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1920, 0, 1080);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1366, 768);
	glutCreateWindow("Icy Jump");
	myinit();
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(specialDown);
	glutSpecialUpFunc(specialUp);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000/FPS,timmer,60);
	glutMainLoop();
}