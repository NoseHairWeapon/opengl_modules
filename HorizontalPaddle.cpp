#include "HorizontalPaddle.h"
#include "glut.h"

bool HorizontalPaddle::intersectBall(Ball const &_ball) {
	if (
		((_ball.m_position.y >= m_position.y)
			&& (_ball.m_lastposition.y < m_position.y))
		||
		((_ball.m_position.y < m_position.y)
			&& (_ball.m_lastposition.y >= m_position.y))
		) {
		if (
			(_ball.m_position.x >= m_position.x)
			&& (_ball.m_position.x < m_position.x + m_width)
			)
			return true;
	}
	return false;
}

void HorizontalPaddle::draw() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);			//GLbitfield mask
	
	GLfloat range[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE,range);		//GLenum pname, GLfloat *params

	glLineWidth(range[1]);	//GLfloat width

	glBegin(GL_LINES);			//GLenum mode
	{
		glVertex2f(m_position.x, m_position.y);				//GLfloat x, GLfloat y
		glVertex2fv((GLfloat *)&(m_position + vec2(m_width, 0)));			//const GLfloat *v
	}
	glEnd();

	glPopAttrib();
}