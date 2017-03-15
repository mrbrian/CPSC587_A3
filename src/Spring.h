#pragma once

#include "Vec3f.h"
#include "Mat4f.h"
#include "glad/glad.h"
#include "Mass.h"
#include <vector>

class Spring 
{
public:
	Spring();
	~Spring();

	float k;
	float x_rest;
	float damp;

	std::vector<Vec3f> verts;
	Mass *mass_1;
	Mass *mass_2;
	Vec3f color;

	GLuint vertBufferID;
	GLuint vaoID;;

	Vec3f getForce();
	Vec3f getX(float dt);
	Vec3f getVel(float dt);
	void applyForce(float dt);
	void update(float dt);

    void updateGPU();
	void render();
	void load();
};

