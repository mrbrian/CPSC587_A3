#include "Spring.h"

extern void reloadColorUniform(float r, float g, float b);

Spring::Spring() : Mass()
{
	mass = new Mass();
	Mass &m = *mass;
	m.mass = 1;
	m.pos = new Vec3f(0, -1.5, 0);

	pos = new Vec3f(0, 0, 0);
	k = 1;
	x_rest = 1;
	mass = &m;
	color = Vec3f(1, 1, 1);
}

Spring::~Spring()
{
}

float Spring::getForce()
{
	float dist = (*mass->pos - *pos).length();
	float F = k * (x_rest - dist);
	return F;
}

Vec3f Spring::getX(float dt)
{
	Vec3f x = *mass->pos + getVel(dt) * dt;
	return x;
}

Vec3f Spring::getVel(float dt)
{
	Vec3f rest_pt = (*mass->pos - *pos).normalized() * x_rest + *pos;
	Vec3f v = mass->vel - k * (*mass->pos - rest_pt) * dt;
	return v;
}

void Spring::update(float dt)
{
	Vec3f x = getX(dt);
	Vec3f v = getVel(dt);
	Vec3f &mass_pos = *mass->pos;
	mass_pos = x;
	mass->vel = v;
}

void Spring::render()
{    
    verts.clear();
	verts.push_back(*pos);
    verts.push_back(*mass->pos);

	reloadColorUniform(color.x(), color.y(), color.z());

	// Use VAO that holds buffer bindings
	// and attribute config of buffers
	glBindVertexArray(vaoID);
	updateGPU();

	// Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);

	if (mass)
		mass->render();
}

void Spring::load()
{
	glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    verts.clear();
    verts.push_back(Vec3f(0,0,0));
    verts.push_back(Vec3f(0,-5,0));

    glGenBuffers(1, &vertBufferID);
    updateGPU();

	mass->load();
}

void Spring::updateGPU()
{
    //upload to gpu
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID);

    glBufferData(GL_ARRAY_BUFFER,
        sizeof(Vec3f) * 2, // byte size of Vec3f, 2 of them
        verts.data(),      // pointer (Vec3f*) to contents of verts
        GL_STREAM_DRAW);   // Usage pattern of GPU buffer

	glVertexAttribPointer(0,        // attribute layout # above
		3,        // # of components (ie XYZ )
		GL_FLOAT, // type of components
		GL_FALSE, // need to be normalized?
		0,        // stride
		(void *)0 // array buffer offset
	);

    glEnableVertexAttribArray(0);

}
