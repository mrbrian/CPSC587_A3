#include "Spring.h"
#include <vector>
#include <random>

class Model
{
public:
    std::vector<Spring*> springs;
    std::vector<Mass*> masses;

	std::mt19937 MersenneTwisterPRNG;
	std::uniform_real_distribution<double> m_URD;
	
	Vec3f calcNormal(Vec3f a, Vec3f b, Vec3f c)
	{
		Vec3f ab = a - b;
		Vec3f ac = a - c;

		Vec3f norm = ab.crossProduct(ac);
		norm.normalize();
		return norm;
	}

	double RAND_1()
	{
		return (2.0 * m_URD(MersenneTwisterPRNG) - 1.0);    // [-1,1]
	}

    virtual void init();
    virtual void render();
    virtual void update(float dt);
};

// single spring
class Model1 : public Model
{
    void init() override;
};

// series of springs
class Model2 : public Model
{
    void init() override;
};

struct Face
{
    int v_indices[3];

    Face(int i, int j, int k)
    {
        v_indices[0] = i;
        v_indices[1] = j;
        v_indices[2] = k;
    }
};

// jello cube
class Model3 : public Model
{
    std::vector<Face> faces;
    std::vector<Vec3f> verts;
    void init() override;
    void update(float dt) override;
};

// hanging cloth
class Model4 : public Model
{
	void init() override;
};

// flag + wind
class Model5 : public Model
{
    GLuint normBufferID;
    GLuint vertBufferID;
    GLuint vaoID;;

    std::vector<Face> faces;
    std::vector<Vec3f> verts;
    std::vector<Vec3f> normals;
	Vec3f *v_normals;

    float time;
    void init() override;
    void update(float dt) override;
    void updateGPU();
	void updateNormals();
    void render();
};

extern void reloadColorUniform(float r, float g, float b);