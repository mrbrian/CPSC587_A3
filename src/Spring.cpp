#include "Spring.h"

extern void reloadColorUniform(float r, float g, float b);

Spring::Spring()
{
	mass_2 = new Mass();
	mass_2->mass = 1;
	mass_2->pos = Vec3f(0, -1.5, 0);

	mass_1 = new Mass();
	mass_1->pos = Vec3f(0, 0, 0);
	mass_1->mass = 1;
	k = 1;
	damp = 0.25f;
	x_rest = 1;
}

Spring::~Spring()
{
	k = 1;
}

Vec3f Spring::getForce()
{
	float dist = (mass_2->pos - mass_1->pos).length();
	Vec3f F = -k * (dist - x_rest) * (mass_2->pos - mass_1->pos) / dist;
	return F;
}

Vec3f Spring::getX(float dt)
{
	Vec3f x = mass_2->pos + getVel(dt) * dt;
	return x;
}

Vec3f Spring::getVel(float dt)
{
	Vec3f rest_pt = (mass_2->pos - mass_1->pos).normalized() * x_rest + mass_1->pos;
	Vec3f v = mass_2->vel - k * (mass_2->pos - rest_pt) * dt;
	return v;
}

void Spring::applyForce(float dt)
{
	Vec3f a_b = (mass_2->pos - mass_1->pos).normalized();

	mass_1->force += -getForce() - damp * mass_1->vel.dotProduct(a_b) * a_b;
	mass_2->force += getForce() - damp * mass_2->vel.dotProduct(a_b) * a_b;
}

void Spring::update(float dt)
{
	if (!mass_1->fixed)
	{
		mass_1->vel -= getForce() / mass_1->mass * dt;
		mass_1->pos += mass_1->vel * dt;
	}

	if (!mass_2->fixed)
	{
		Vec3f &pos2 = mass_2->pos;
		mass_2->vel += getForce() / mass_2->mass * dt;
		mass_2->pos += mass_2->vel * dt;
	}
}

void Spring::render()
{    
	verts.clear();
	verts.push_back(mass_1->pos);
    verts.push_back(mass_2->pos);

	reloadColorUniform(color.x(), color.y(), color.z());

	// Use VAO that holds buffer bindings
	// and attribute config of buffers
	glBindVertexArray(vaoID);
	updateGPU();

	// Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);

	if (mass_1)
		mass_1->render();

	if (mass_2)
		mass_2->render();
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

	mass_1->load();
	mass_2->load();
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
