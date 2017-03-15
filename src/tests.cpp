#include "glm/glm.hpp"
#include "Spring.h"
#include <iostream>

void test_create()
{
	Mass m = Mass();
	m.mass = 1;
	m.pos = new Vec3f(0, -2, 0);
	m.vel = Vec3f(0, 0, 0);
	Spring s = Spring();
	s.pos = new Vec3f(0, -1, 0);
	s.k = 0.1f;
	s.x_rest = 1;
	s.mass = &m;

	float dt = 1.0f / 30.0f;
	while (true)
	{
		Vec3f x = s.getX(dt);
		Vec3f v = s.getVel(dt);
		Vec3f &mp = *s.mass->pos;
		mp = x;
		s.mass->vel = v;

		printf("%f %f %f\n", x.x(), x.y(), x.z());
	}
	int i;
	std::cin >> i;
}

void test_create2()
{
	Mass m = Mass();
	m.mass = 1;
	m.pos = new Vec3f(0, -0.5f, 0);
	m.vel = Vec3f(0, 0, 0);
	Spring s = Spring();
	s.pos = new Vec3f(0, 0, 0);
	s.k = 0.1f;
	s.x_rest = 1;
	s.mass = &m;

	Spring s2 = Spring();
	s2.pos = s.mass->pos;
	s2.k = 0.1f;
	s2.x_rest = 1;
	s2.mass = &m;

	float dt = 1.0f / 30.0f;
	while (true)
	{
		Vec3f x = s.getX(dt);
		Vec3f v = s.getVel(dt);
		Vec3f &mp = *s.mass->pos;
		mp = x;
		s.mass->vel = v;

		printf("%f %f %f\n", x.x(), x.y(), x.z());
	}
	int i;
	std::cin >> i;
}

int main(int argc, char** argv)
{
	//test_create2();
	test_create();
	return 0;
}
