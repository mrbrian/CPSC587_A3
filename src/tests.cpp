#include "glm/glm.hpp"
#include "Spring.h"
#include <iostream>

void test_create()
{
	Mass m = Mass();
	m.mass = 1;
	m.pos = Vec3f(0, -2, 0);

	Spring s = Spring();
	s.pos = Vec3f(0, 0, 0);
	s.k = 0.1f;
	s.x_rest = 1;
	s.mass = &m;

	float dt = 1.0f / 30.0f;
	printf("%f\n", s.getForce());
	while (true)
	{
		Vec3f x = s.getX(dt);
		Vec3f v = s.getVel(dt);
		s.mass->pos += v * dt;
		s.mass->vel = v;

		printf("%f %f %f\n", x.x(), x.y(), x.z());
	}
	int i;
	std::cin >> i;
}

int main(int argc, char** argv)
{
	test_create();
	return 0;
}
