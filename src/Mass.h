#pragma once

#include "Vec3f.h"
#include <vector>
#include "glad/glad.h"

class Mass
{
public:
	Mass();
	
	Vec3f pos;   // can reference another mass (spring)
	Vec3f vel;
	float mass;

	Vec3f color;
	virtual void update(float dt);
	virtual void render();
	virtual void load();
	virtual void updateGPU();
	const Vec3f gravity = Vec3f(0, -9.81, 0);

	GLuint vertBufferID;
	GLuint vaoID;;
};


