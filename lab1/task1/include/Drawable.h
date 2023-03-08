#pragma once

struct Drawable
{
	virtual ~Drawable() = default;

	virtual void Draw(float x, float y) const = 0;
};
