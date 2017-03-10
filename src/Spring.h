#include "Vec3f.h"
#include "Mat4f.h"
#include "glad\glad.h"

class Spring
{
public:
	Spring();
	~Spring();

	float k;
	float x_rest;
	float x_curr;
	float vel;

	bool fixed;

	Vec3f pos;
	Vec3f color;
	Vec3f velocity;

	Mat4f M;
	GLuint vertBufferID;
	GLuint vaoID;

	void render();
	void load();
	void update();
};

