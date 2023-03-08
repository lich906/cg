#include "LetterA.h"

LetterA::LetterA(float boxWidth, float boxHeight, Color color)
	: m_boxWidth(boxWidth)
	, m_boxHeight(boxHeight)
	, m_color(color)
{
}

void LetterA::Draw(float x, float y) const
{
	glColor3f(m_color.r, m_color.g, m_color.b);

	glBegin(GL_TRIANGLE_STRIP);

	/*
		   /
		  /
		 /
		/
	*/

	glVertex2f(x, y + (m_boxHeight * 0.2f));
	glVertex2f(x, y);
	glVertex2f(x + (m_boxWidth * 0.5f), y + m_boxHeight);
	glVertex2f(x + (m_boxWidth * 0.5f), y + (m_boxHeight * 0.8f));

	glEnd();

	glBegin(GL_TRIANGLE_STRIP);

	/*
		   /\
		  /  \
		 /    \
		/      \
	*/

	glVertex2f(x + (m_boxWidth * 0.5f), y + (m_boxHeight * 0.8f));
	glVertex2f(x + (m_boxWidth * 0.5f), y + m_boxHeight);
	glVertex2f(x + m_boxWidth, y);
	glVertex2f(x + m_boxWidth, y + (m_boxHeight * 0.2f));

	glEnd();

	glBegin(GL_TRIANGLE_STRIP);

	/*
		   /\
		  /  \
		 /----\
		/      \
	*/

	glVertex2f(x + (m_boxWidth * 0.15f), y + (m_boxHeight * 0.4f));
	glVertex2f(x + (m_boxWidth * 0.15f), y + (m_boxHeight * 0.3f));
	glVertex2f(x + (m_boxWidth * 0.85f), y + (m_boxHeight * 0.4f));
	glVertex2f(x + (m_boxWidth * 0.85f), y + (m_boxHeight * 0.3f));

	glEnd();
}
