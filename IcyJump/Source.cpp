#include<GL/glut.h>



void render()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}



int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Icy Jump");
	glutDisplayFunc(render);
	glutMainLoop();



}