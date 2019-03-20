#include <stdio.h>
#include <stdarg.h>
#include "font.h"
#include "glm\glm.hpp"
#include "glut.h"

using namespace glm;

static vec2 position;
static float height = FONT_DEFUALT_HEIGHT;
static float weight = 1;

void fontBegin(){
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);	//GLbitfield mask

	glMatrixMode(GL_PROJECTION);	//glenum mode
	glLoadIdentity();

	GLint viewport[4];
	glGetIntegerv(
		GL_VIEWPORT,//GLenum pname,
		viewport// GLint *params
	);		
	gluOrtho2D(
		0, viewport[2],//GLdouble left, GLdouble right,
		viewport[3], //GLdouble bottom,
		0 //GLdouble top
	);

	glMatrixMode(GL_MODELVIEW);	//glenum mode
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);	//GLenum cap
	glDisable(GL_LIGHTING);	//GLenum cap
	glDisable(GL_TEXTURE_2D);	//GLenum cap
}

void fontEnd(){
	glPopMatrix();
	glPopAttrib();
}

void fontSetPosition(float _x, float _y){
	position = vec2(_x, _y);
}

void fontSetHeight(float _height){
	height = _height;
}

float fontGetWidth() {
	return FONT_DEFUALT_WIDTH * height / FONT_DEFUALT_HEIGHT;
}

float fontGetHeight() {
	return height;
}

float fontGetWeightMin(){
	GLfloat weight[2];
	glGetFloatv(		//GLenum pname, GLfloat *params
		GL_LINE_WIDTH_RANGE,
		weight);
	return weight[0];
}

float fontGetWeightMax(){
	GLfloat weight[2];
	glGetFloatv(
		GL_LINE_WIDTH_RANGE,	//GLenum pname, GLfloat *params
		weight);
	return weight[1];
}

void fontSetWeight(float _weight){
	weight = _weight;
}

float fontGetWeight() {
	return weight;
}

void fontDraw(const char *_format, ...){
	va_list argList;
	va_start(argList, _format);
	char str[256];
	vsprintf_s(str, _format, argList);
	va_end(argList);

	glLineWidth(weight);	//GLfloat width

	char *p = str;
	glPushMatrix();
	{
		glTranslatef(position.x, position.y + height, 0);	//GLfloat x, GLfloat y, GLfloat z
		float s = height / FONT_DEFUALT_HEIGHT;
		glScalef(s,-s,s);	//xyz
		for (; (*p != '\0') && (*p != '\n'); p++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}
	glPopMatrix();
	
	if (*p == '\n') {
		glTranslatef(0, height + weight * 2, 0);	//GLfloat x, GLfloat y, GLfloat z
		fontDraw(++p);
	}
}