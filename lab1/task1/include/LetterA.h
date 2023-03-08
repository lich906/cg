#pragma once

#include "Color.h"
#include "Drawable.h"

class LetterA : public Drawable
{
public:
	LetterA(float boxWidth, float boxHeight, Color color);

	void Draw(float x, float y) const override;

private:
	float m_boxWidth, m_boxHeight;
	Color m_color;
};
