#include<GL/glut.h>
#include<stdio.h>
#define FPS 60
#define TIMESTEP 1.0/60.0
float v[2] = { 0,0 };
float initial_velocity_horizontal = 0, velocity_horizontal = 0, initial_velocity_vertical=0, velocity_vertical=0, acceleration_horizontal = 0 , acceleration_vertical=0 ;
float displacement_x = 0, displacement_y = 0;
float time_x = TIMESTEP, time_y = TIMESTEP;
float friction_left = 0, friction_right =0;
bool canJump = true;
int jumpFinish = 0;
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
	{
		v[0] = 1870;
		initial_velocity_horizontal = 0;
		//time_x = 0;
	}
	if (v[0] < 0)
	{
		v[0] = 0;
		initial_velocity_horizontal = 0;
	//	time_x = 0;
	}
}
void move_vertical(float *v, float dy)
{
	v[1] += dy;
	if (v[1] > 1030)
	{
		v[1] = 1030;
		initial_velocity_vertical = 0;
		//time_y = 0;
	}
	if (v[1] < 0)
	{
		v[1] = 0;
		initial_velocity_vertical = 0;
		if (!canJump)
		{
			canJump = true;
			jumpFinish = 1;
		}
	}
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
void move_object()
{
	
		move_vertical(v, displacement_y);
		move_horizontal(v, displacement_x);

}

void compute_velocity()
{
	velocity_vertical = initial_velocity_vertical + acceleration_vertical*TIMESTEP;
	if ((velocity_horizontal = initial_velocity_horizontal + acceleration_horizontal*TIMESTEP )> 2000)
		velocity_horizontal = 2000;
	
}

void compute_displacement()
{
	
	displacement_x = (initial_velocity_horizontal *time_x) + 0.5 *acceleration_horizontal * time_x * time_x;
	displacement_y = (initial_velocity_vertical * time_y) + 0.5 * acceleration_vertical * time_y *time_y;
	initial_velocity_horizontal = velocity_horizontal;
	initial_velocity_vertical = velocity_vertical;
}

void timmer(int x)
{
	if (keys[0])
	{
		
		if (canJump)
		{
			acceleration_vertical = 100000;
			
		}
		else
		{
			acceleration_vertical = -5000;
		}
		
	}
	else
	{
		acceleration_vertical = -7500;
		
	}
	if (keys[2] && canJump)
	{
		acceleration_horizontal = -8000;
	}
	else if (keys[3] && canJump)
		acceleration_horizontal = 8000;
	else
	{
		if (jumpFinish == 1)
		{
			if (initial_velocity_horizontal > 100 && canJump)
				acceleration_horizontal = -70000;
			else if (initial_velocity_horizontal < -100 && canJump)
				acceleration_horizontal = 70000;
			else if (canJump)
			{
				initial_velocity_horizontal = 0;
				acceleration_horizontal = 0;
			}
			jumpFinish = 0;
		}
		else
		{
			if (initial_velocity_horizontal > 100 && canJump)
				acceleration_horizontal = -2000;
			else if (initial_velocity_horizontal < -100 && canJump)
				acceleration_horizontal = 2000;
			else if (canJump)
			{
				initial_velocity_horizontal = 0;
				acceleration_horizontal = 0;
			}
		}
	}
	compute_velocity();
	compute_displacement();
	move_object();

	if (acceleration_vertical == 100000)
	{
		canJump = false;
		acceleration_horizontal = 0;

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