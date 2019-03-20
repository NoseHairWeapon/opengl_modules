#include "Ball.h"
#include "glut.h"

void Ball::update() {
	m_lastposition = m_position;
	m_position += m_speed;
}

void Ball::draw() {
	glPushMatrix();
	{
		glTranslatef(m_position.x, m_position.y, 0);	//GLfloat x, GLfloat y, GLfloat z
		glScalef(m_radius,m_radius,0);	//GLFloat x,y,z
		glutSolidSphere(	//GLdouble radius, GLint slices, GLint stacks
			1,
			16,
			16);
	}
	glPopMatrix();
}