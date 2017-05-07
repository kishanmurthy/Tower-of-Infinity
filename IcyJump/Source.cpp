#include<GL/glut.h>
#include<iostream>
#include<stdio.h>
#include "Player.h"
#include "KeyboardBuffer.h"
#include "GameLayout.h"
using namespace std;
#define FPS 60

GameLayout gameLayout;
Player player(gameLayout);

bool KeyboardBuffer::keys[4] = { false };


void render()
{
	glClearColor(0,0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	player.gameLayout.draw_layout();
	
	glColor3f(0,0.5,0.7);
	glRectf(player.playerBlock.x1, player.playerBlock.y1, player.playerBlock.x2, player.playerBlock.y2);
	glFlush();
}

void timmer(int x)
{
	if (KeyboardBuffer::keys[0])
	{
		
		if (player.canJump)
		{
			player.acceleration_vertical = 120000;
			
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
	if (KeyboardBuffer::keys[2] && player.canJump)
	{
		player.acceleration_horizontal = -8000;
	}
	else if (KeyboardBuffer::keys[3] && player.canJump)
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

	if (player.acceleration_vertical == 120000)
	{
		player.canJump = false;
		player.acceleration_horizontal = 0;

	}
	if (player.checkThreshold())
	{
		cout << "Threshold Reched" << endl;
		player.decrementAllObjects();
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
	glutKeyboardFunc(&(KeyboardBuffer::keyboardDown));
	glutKeyboardUpFunc(&(KeyboardBuffer::keyboardUp));
	glutSpecialFunc(&(KeyboardBuffer::specialDown));
	glutSpecialUpFunc(&(KeyboardBuffer::specialUp));
	glutReshapeFunc(reshape);
	glutTimerFunc(1000/FPS,timmer,60);
	glutMainLoop();
}