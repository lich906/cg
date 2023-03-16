#include "model/normalize_vector.h"

Vector NormalizeVector(const Vector& v, int w, int h)
{
	return { 2 * v.x / w - 1, 1 - 2 * v.y / h };
}
