#include "Spring.h"

Spring::Spring() : Mass()
{
	mass = new Mass();
	Mass &m = *mass;
	m.mass = 1;
	m.pos = Vec3f(0, -2, 0);

	pos = Vec3f(0, 0, 0);
	k = 0.1f;
	x_rest = 1;
	mass = &m;
}

Spring::~Spring()
{
}

float Spring::getForce()
{
	float dist = (mass->pos - pos).length();
	float F = k * (x_rest - dist);
	return F;
}

Vec3f Spring::getX(float dt)
{
	Vec3f x = mass->pos + getVel(dt) * dt;
	x = mass->pos * (1 - k*(dt*dt)) + mass->vel * dt;
	return x;
}

Vec3f Spring::getVel(float dt)
{
	Vec3f v = mass->vel - k * mass->pos * dt;
	return v;
}

void Spring::update(float dt)
{
	Vec3f x = getX(dt);
	Vec3f v = getVel(dt);
	mass->pos += v * dt;
	mass->vel = v;
}

void Spring::render()
{    
    /*verts.clear();
	verts.push_back(pos);
    verts.push_back(mass->pos);*/

	// Use VAO that holds buffer bindings
	// and attribute config of buffers
	glBindVertexArray(vaoID);
	// Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_LINES, 0, 2);
}

void Spring::load()
{
	glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    verts.clear();
    verts.push_back(Vec3f(0,0,0));
    verts.push_back(Vec3f(0,-1,0));

    //upload to gpu
    glGenBuffers(1, &vertBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID);

    glBufferData(GL_ARRAY_BUFFER,
        sizeof(Vec3f) * 2, // byte size of Vec3f, 2 of them
        verts.data(),      // pointer (Vec3f*) to contents of verts
        GL_STATIC_DRAW);   // Usage pattern of GPU buffer

	glVertexAttribPointer(0,        // attribute layout # above
		3,        // # of components (ie XYZ )
		GL_FLOAT, // type of components
		GL_FALSE, // need to be normalized?
		0,        // stride
		(void *)0 // array buffer offset
	);

    glEnableVertexAttribArray(0);

}
