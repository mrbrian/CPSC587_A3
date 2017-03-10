#include "Vec3f.h"
#include "Mat4f.h"
#include "glad\glad.h"
#include "Mass.h"
#include <vector>

class Spring : public Mass
{
public:
	Spring();
	~Spring();

	float getForce();

	Vec3f getX(float dt);

	Vec3f getVel(float dt);

	void update(float dt);

	float k;
	float x_rest;
	bool fixed;

	std::vector<Vec3f> verts;
	GLuint vertBufferID;
	GLuint vaoID;
	Mass *mass;

	void render();
	void load();
};

