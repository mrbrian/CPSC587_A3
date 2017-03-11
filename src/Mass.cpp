#include "Mass.h"
#include "glad/glad.h"

Mass::Mass()
{
}

void Mass::render()
{
	// Use VAO that holds buffer bindings
	// and attribute config of buffers
	glBindVertexArray(vaoID);
	updateGPU();

	// Draw Quads, start at vertex 0, draw 4 of them (for a quad)
	glPointSize(10);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
}

void Mass::load()
{
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	glGenBuffers(1, &vertBufferID);
	updateGPU();
}

void Mass::update(float dt)
{
	pos += vel * dt;
}

void Mass::updateGPU()
{
	//upload to gpu
	glBindBuffer(GL_ARRAY_BUFFER, vertBufferID);

	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vec3f), // byte size of Vec3f, 2 of them
		&pos,      // pointer (Vec3f*) to contents of verts
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
