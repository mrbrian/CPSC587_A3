#include "Vec3f.h"

class Mass
{
	Mass();

	Vec3f pos;
	Vec3f velocity;
	const Vec3f gravity = Vec3f(0, -9.81, 0);
	float mass;
};