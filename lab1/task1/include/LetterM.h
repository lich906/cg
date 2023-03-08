#pragma once

#include <type_traits>

#include "Color.h"
#include "Drawable.h"

class LetterM : public Drawable
{
public:
	LetterM(float boxWidth, float boxHeight, Color color);

	void Draw(float x, float y) const override;

private:
	float m_boxWidth, m_boxHeight;
	Color m_color;
};
