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
int Block::count;
bool out = false;
void render()
{
	glClearColor(230.0/255, 255.0 / 255, 240.0 / 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	player.gameLayout.draw_layout();
	player.gameLayout.draw_player(player.playerBlock);
	if (out)
		player.gameLayout.draw_game_over();
	glFlush();
}

void timmer(int x)
{
	player.setAcceleration(KeyboardBuffer::keys);
	player.compute_velocity();
	player.compute_displacement();
	player.move_object();
	player.resetHorizontalAccelerationifJump();
	player.gameLayout.updateBlocks();
	player.verticalScrolling();
	player.updateScrollingSpeed();
	
	if (player.checkThreshold())
		player.decrementAllObjects();
	

	
	
	if (player.isOut())
		out = true;
	else {
		
		glutTimerFunc(1000 / FPS, timmer, 60);
	}
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

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Icy Jump");
	myinit();
	glutFullScreen();
	glutDisplayFunc(render);
	glutKeyboardFunc(&(KeyboardBuffer::keyboardDown));
	glutKeyboardUpFunc(&(KeyboardBuffer::keyboardUp));
	glutSpecialFunc(&(KeyboardBuffer::specialDown));
	glutSpecialUpFunc(&(KeyboardBuffer::specialUp));
	glutReshapeFunc(reshape);
	glutTimerFunc(1000/FPS,timmer,60);
	glutMainLoop();
}