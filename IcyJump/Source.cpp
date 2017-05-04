#include<GL/glut.h>
#include<stdio.h>

float v[2] = { 0,0 };
bool keys[4] = { false };
void render()
{
	glClearColor(0,0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0);
	glRectf(v[0], v[1], v[0]+50, v[1]+50);
	glFlush();
}
void move_horizontal(float *v, float dx)
{	
	v[0] += dx;
	if (v[0] > 1870)
		v[0] = 1870;
	if (v[0] < 0)
		v[0] = 0;
	
}
void move_vertical(float *v, float dy)
{
	v[1] += dy;
	if (v[1] > 1030)
		v[1] = 1030;
	if (v[1] < 0)
		v[1] = 0;

}

void keyboardDown(unsigned char c,int x,int y)
{
	if (c == 'w' || c ==GLUT_KEY_UP)
		keys[0] = true;
	else if (c == 's')
		keys[1] = true;
	else if (c == 'a')
		keys[2] = true;
	else if (c == 'd')
		keys[3] = true;
	
	printf("%d", c);

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

	printf("%d", c);

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
		move_vertical(v, 50);
	else if(keys[1])
		move_vertical(v, -50);
	if (keys[2])
		move_horizontal(v, -50);
	else if(keys[3])
		move_horizontal(v, 50);
	glutPostRedisplay();
	glutTimerFunc(10, timmer, 60);

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
	glutTimerFunc(100,timmer,60);
	glutMainLoop();
}