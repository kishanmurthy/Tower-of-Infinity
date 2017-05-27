#include<GL/glut.h>
#include<iostream>
#include<stdio.h>
#include "Player.h"
#include "KeyboardBuffer.h"
#include "GameLayout.h"
#include "MenuLayout.h"
#include "ContolLayout.h"
using namespace std;
#define FPS 60
MenuLayout menuLayout;
GameLayout gameLayout;
ControlLayout controlLayout;
Player player(gameLayout);
bool KeyboardBuffer::keys[6] = { false };
bool KeyboardBuffer::isControllerInUse = true;
int Block::count;
bool out = false;
int state = 0;
bool checkEscKey()
{
	if (KeyboardBuffer::keys[5])
	{
		KeyboardBuffer::keys[5] = false;
		return true;
	}
	return false;
}
void render()
{
	glClearColor(230.0/255, 255.0 / 255, 240.0 / 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	if (state == 0)
	{
		menuLayout.draw_layout();
	
	}
	else if (state == 1 || state == 4)
	{
		player.gameLayout.draw_layout();
		player.gameLayout.draw_player(player.playerBlock);
		if (state == 4)
			player.gameLayout.draw_game_over();
	}
	else if (state == 2)
	{
		controlLayout.draw_layout_keyboard();
	}
	else if (state == 3)
	{
		controlLayout.draw_layout_controller();
	}
	
	glutSwapBuffers();
}


void timmer(int x)
{
	if (state == 0)
	{

		int option = menuLayout.get_option(KeyboardBuffer::keys);
		if (option > -1)
			state = option + 1;
		if(state==1)
			player.reset();
	}
	else if (state == 1)
	{
		player.setAcceleration(KeyboardBuffer::keys);
		player.compute_physics();
		player.move_object();
		player.resetHorizontalAccelerationifJump();
		player.gameLayout.updateBlocks();
		player.verticalScrolling();
		player.updateScrollingSpeed();
		if (player.checkThreshold())
			player.decrementAllObjects();
		if(checkEscKey())
			state = 0;
	
		if (player.isOut())
			state = 4;

	}
	else if (state == 2)
	{
		if (checkEscKey())
			state = 0;
		else if (KeyboardBuffer::keys[3])
			state = 3;
	}
	else if (state == 3)
	{
		if (checkEscKey())
			state = 0;
		else if (KeyboardBuffer::keys[2])
			state = 2;
	}
	else if (state == 4)
	{
		if (checkEscKey())
			state = 0;
	}
	glutTimerFunc(1000 / FPS, timmer, 60);
	glutPostRedisplay();
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
void joystick(unsigned int b, int x, int y, int z)
{
	if (x > 200)
		KeyboardBuffer::keys[1] = true;
	else if (x < -200)
		printf("Left\n");
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("TOWER OF INFINITY");
	myinit();
	glutFullScreen();
	glutDisplayFunc(render);
	glutKeyboardFunc(&(KeyboardBuffer::keyboardDown));
	glutKeyboardUpFunc(&(KeyboardBuffer::keyboardUp));
	glutSpecialFunc(&(KeyboardBuffer::specialDown));
	glutSpecialUpFunc(&(KeyboardBuffer::specialUp));
	glutJoystickFunc(&KeyboardBuffer::controller,1000/FPS);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000/FPS,timmer,60);
	glutMainLoop();
}

