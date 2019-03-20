#include<stdio.h>
#include <time.h>
#include"glm\glm.hpp"
#include"glut.h"
#include "audio.h"
#include "font.h"

using namespace glm;

ivec2 windowsSize = { 800,600 };

bool keys[256];

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);	//glenum mode
	glLoadIdentity();
	gluOrtho2D(
		0, windowsSize.x,//GLdouble left, GLdouble right,
		windowsSize.y, //GLdouble bottom,
		0 //GLdouble top
	);

	glMatrixMode(GL_MODELVIEW);	//glenum mode
	glLoadIdentity();

	fontBegin();
	fontSetHeight(FONT_DEFUALT_HEIGHT);
	fontSetPosition(0,0);
	//fontDraw("");
	fontEnd();

	glutSwapBuffers();
}

void idle(int value) {
	audioUpdate();
	glutPostRedisplay();

	glutTimerFunc(
		1000 / 60,	//unsigned int millis
		idle,		//void 
		0 );		// int value
}

void reshape(int width, int height) {
	printf("reshape: width: %d height: %d\n", width, height);
	glViewport(
		0,0,// GLint x, GLint y, 
		width, height //GLsizei width, GLsizei height
	);
	windowsSize = ivec2(width,height);
}

void Keyboard(unsigned char key, int x, int y){
	printf("keyboard: \' %c\' (%#x)\n", key, key);
	if (key == 0x1b)
		exit(0);

	keys[key] = true;
}

void KeyboardUp(unsigned char key, int x, int y) {
	printf("keyboardUp: \' %c\' (%#x)\n", key, key);
	keys[key] = false;
}

void PassiveMotion(int x, int y) {
	printf("passiveMotion: x:%d y: %d\n", x, y);
}

int main(int argc, char **argv) {
	audioInit();

	glutInit(
		&argc, //int *argcp
		argv);
	glutInitDisplayMode(GL_DOUBLE);	//unsigned int mode
	glutInitWindowPosition(640, 0);	// int x,y
	glutInitWindowSize(windowsSize.x, windowsSize.y);	// int width, height
	glutCreateWindow("title");	//Å@const char *title
	glutDisplayFunc(display);	//void (GLUTCALLBACK *func)(void)
	glutTimerFunc(
		0,//unsigned int millis
		idle,// void (GULTCALLBACK *func)(int value)
		0// int value
	);
	glutReshapeFunc(reshape);	//void (GLUTCALLBACK void)
	glutKeyboardFunc(Keyboard);	//void (GLUTCALLBACK *func)(unsigned char key, int x, int y
	glutKeyboardUpFunc(KeyboardUp);		//void (GLUTCALLBACK *func)(unsigned char key, int x, int y
	//glutMotionFunc(Motion);					//void (GLUTCALLBACK *func)(int x, int y
	glutIgnoreKeyRepeat(GL_TRUE);	//int ignore
	glutPassiveMotionFunc(PassiveMotion);			//void (GLUTCALLBACK *func)(int x, int y
	glutMainLoop();
}