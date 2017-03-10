#include "Spring.h"

Spring::Spring()
{
}

Spring::~Spring()
{
}

void Spring::update()
{
}

void Spring::render()
{
	/*Mat4f MVP = P * V * M;
	reloadMVPUniform();
	reloadColorUniform(1, 0, 1);
	// Use VAO that holds buffer bindings
	// and attribute config of buffers
	glBindVertexArray(vaoID);
	// Draw Quads, start at vertex 0, draw 4 of them (for a quad)
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// flatten and draw shadow
	M = TranslateMatrix(0, 0.1f, 0) * ScaleMatrix(1, 0.01f, 1) * cars_M[i];
	MVP = P * V * M;
	reloadMVPUniform();
	reloadColorUniform(0, 0, 0);
	// Use VAO that holds buffer bindings
	// and attribute config of buffers
	glBindVertexArray(vaoID);
	// Draw Quads, start at vertex 0, draw 4 of them (for a quad)
	glDrawArrays(GL_TRIANGLES, 0, 36);*/
}

void Spring::load()
{/*
	// Just basic layout of floats, for a quad
	// 3 floats per vertex, 4 vertices
	std::vector<Vec3f> verts;
	verts.push_back(Vec3f(1, 0, -1));
	verts.push_back(Vec3f(-1, 0, -1));
	verts.push_back(Vec3f(1, 0, 1));
	verts.push_back(Vec3f(-1, 0, 1));

	glBindBuffer(GL_ARRAY_BUFFER, vertBufferID);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
		verts.data(),      // pointer (Vec3f*) to contents of verts
		GL_STATIC_DRAW);   // Usage pattern of GPU buffer*/

}
