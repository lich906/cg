#include "LetterM.h"

LetterM::LetterM(float boxWidth, float boxHeight, Color color)
	: m_boxWidth(boxWidth)
	, m_boxHeight(boxHeight)
	, m_color(std::move(color))
{
}

void LetterM::Draw(float x, float y) const
{
	glColor3f(m_color.r, m_color.g, m_color.b);

	glBegin(GL_TRIANGLE_STRIP);

	glVertex2f(x, y);
	glVertex2f(x, y + m_boxHeight);
	glVertex2f(x + (m_boxWidth * 0.2f), y);
	glVertex2f(x + (m_boxWidth * 0.2f), y + m_boxHeight);

	/*
		|
		|
		|
		|
	*/

	glEnd();

	glBegin(GL_TRIANGLES);

	glVertex2f(x + (m_boxWidth * 0.2f), y + m_boxHeight);
	glVertex2f(x + (m_boxWidth * 0.2f), y + (m_boxHeight * 0.8));
	glVertex2f(x + (m_boxWidth * 0.5f), y + (m_boxHeight * 0.5));

	/*
		|\
		| \
		|
		|
	*/

	glVertex2f(x + (m_boxWidth * 0.5f), y + (m_boxHeight * 0.5));
	glVertex2f(x + (m_boxWidth * 0.8f), y + m_boxHeight);
	glVertex2f(x + (m_boxWidth * 0.8f), y + (m_boxHeight * 0.8));

	/*
		|\  /
		| \/
		|
		|
	*/

	glEnd();

	glBegin(GL_TRIANGLE_STRIP);

	glVertex2f(x + (m_boxWidth * 0.8f), y);
	glVertex2f(x + (m_boxWidth * 0.8f), y + m_boxHeight);
	glVertex2f(x + m_boxWidth, y);
	glVertex2f(x + m_boxWidth, y + m_boxHeight);

	/*
		|\  /|
		| \/ |
		|    |
		|    |
	*/

	glEnd();
}
