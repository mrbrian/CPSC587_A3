#include "Model.h"
#include <random>

std::mt19937 MersenneTwisterPRNG;
std::uniform_real_distribution<double> m_URD;

double RAND_1()
{
	return (2.0 * m_URD(MersenneTwisterPRNG) - 1.0);    // [-1,1]
}

void Model::render()
{
	for (int i = 0; i < springs.size(); i++)
		springs[i]->render();
}

void Model::init()
{
}

void Model::update(float dt)
{
	for (int i = 0; i < springs.size(); i++)
		springs[i]->applyForce(dt);

	for (int i = 0; i < masses.size(); i++)
	{
		masses[i]->addGravity(dt);
		masses[i]->resolveForce(dt);
	}
}

void Model1::init()
{
	Mass *m_1 = new Mass();
	m_1->mass = 1;
	m_1->pos = Vec3f(0, 1.0f, 0);
	m_1->vel = Vec3f(0, 0, 0);
	m_1->fixed = true;

	Mass *m_2 = new Mass();
	m_2->mass = 1;
	m_2->pos = Vec3f(0, -0.5f, 0);
	m_2->vel = Vec3f(0, 0, 0);

	Spring *s = new Spring();
	s->k = 10;
	s->x_rest = 1;
	s->mass_1 = m_1;
	s->mass_2 = m_2;
	s->color = Vec3f(1, 0, 0);

	springs.push_back(s);
	masses.push_back(m_1);
	masses.push_back(m_2);

	for (int i = 0; i < springs.size(); i++)
		springs[i]->load();
}

void Model2::init()
{
	int num_chains = 10;
	Vec3f start = Vec3f(0, 2, 0);
	float scale = 0.3f;
	Vec3f offset = Vec3f(1, -1, 0).normalized() * scale;
	Mass *prev_mass = 0;

	for (int i = 0; i < num_chains + 1; i++)
	{
		Mass *m = new Mass();
		m->mass = 0.125f;
		m->pos = start + offset * i;
		m->vel = Vec3f(0, 0, 0);
		
		if (i == 0)
			m->fixed = true;

		if (m && prev_mass)
		{
			Spring *s = new Spring();
			s->k = 100;
			s->damp = 0.5f;
			s->x_rest = scale;
			s->mass_1 = prev_mass;
			s->mass_2 = m;
			s->color = Vec3f(1, 0, 0);
			springs.push_back(s);
		}

		masses.push_back(m);
		prev_mass = m;
	}

	for (int i = 0; i < springs.size(); i++)
		springs[i]->load();
}

Vec3f calcNormal(Vec3f a, Vec3f b, Vec3f c)
{
	Vec3f ab = a - b;
	Vec3f ac = a - c;

	Vec3f norm = ab.crossProduct(ac);
	norm.normalize();
	return norm;
}

void Model3::init()
{
    int w = 4;
    int h = 4;
    int depth = 4;
	float scale = 0.3f;
	float max_dist_squared = 3 * scale * scale;
    Vec3f start = Vec3f(-w, -h, -depth) * 0.5f * scale;
	Mass *prev_mass = 0;

	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
			for (int z = 0; z < depth; z++)
			{
				Mass *m = new Mass();
				m->mass = 0.25f;
				m->pos = start + Vec3f(x, y, z) * scale;
				m->vel = Vec3f(0, 0, 0);

				masses.push_back(m);
			}

    for (int i = 0; i < masses.size(); i++)
	{
		Mass *a = masses[i];

        for (int j = 0; j < masses.size(); j++)
		{
			if (i == j)
				continue; 

			Mass *b = masses[j];			
			float dist_sq = (b->pos - a->pos).lengthSquared();

			if (dist_sq > max_dist_squared)
				continue;

			Spring *s = new Spring();
            s->k = 40;
            s->damp = 0.125f;
			s->x_rest = sqrt(dist_sq);
			s->mass_1 = a;
			s->mass_2 = b;
			s->color = Vec3f(1, 0, 0);
			springs.push_back(s);
		}
	}

    for (int i = 0; i < springs.size(); i++)
        springs[i]->load();
}

void Model3::update(float dt)
{
    float floor_y = -1.0f;

	for (int i = 0; i < springs.size(); i++)
		springs[i]->applyForce(dt);

	for (int i = 0; i < masses.size(); i++)
	{
		masses[i]->addGravity(dt);
		masses[i]->resolveForce(dt);
		Vec3f pos = masses[i]->pos;
		if (pos.y() < floor_y) 
		{
			pos.set(pos.x(), floor_y, pos.z());
			masses[i]->pos = pos;
		}
	}
}

void Model4::init()
{
    int w = 10;
    int h = 10;
    float scale = 0.3f;
	float max_dist_squared = 2 * scale * scale;
    Vec3f start = Vec3f(0, 2, 0);
	Mass *mass_heap = new Mass[w * h];
	Mass *prev_mass = 0;

	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			Mass *m = &mass_heap[y * w + x];
            m->mass = 0.05f;
            m->pos = start + Vec3f(x, -y, RAND_1() / 100) * scale;
			m->vel = Vec3f(0, 0, 0);

			masses.push_back(m);
		}

    masses[0]->fixed = true;
    //uymasses[w - 1]->fixed = true;

	for (int i = 0; i < masses.size(); i++)
	{
		Mass *a = masses[i];

		for (int j = 0; j < masses.size(); j++)
		{
			if (i == j)
				continue;

			Mass *b = masses[j];
			float dist_sq = (b->pos - a->pos).lengthSquared();

			if (dist_sq > max_dist_squared + scale / 100)
				continue;

			Spring *s = new Spring();
            s->k = 80;
            s->damp = 0.05f;
			s->x_rest = sqrt(dist_sq);
			s->mass_1 = a;
			s->mass_2 = b;
			s->color = Vec3f(1, 0, 0);
			springs.push_back(s);
		}
	}

	for (int i = 0; i < springs.size(); i++)
		springs[i]->load();

}

void Model5::init()
{
	time = -1;
	int w = 30;
	int h = 15;
	float scale = 0.125f;
	float max_dist_squared = 2 * scale * scale;
	Vec3f start = Vec3f(-w, h, 0) * scale / 2; 
	Mass *mass_heap = new Mass[w * h];
	Mass *prev_mass = 0;

	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
		{
			Mass *m = &mass_heap[y * w + x];
			m->mass = 0.1f;
			m->pos = start + Vec3f(x, -y, 0) * scale;
			m->vel = Vec3f(0, 0, 0);

			masses.push_back(m);
		}

	masses[0]->fixed = true;
	masses[h / 2]->fixed = true;
	masses[h - 1]->fixed = true;

	for (int i = 0; i < masses.size(); i++)
	{
		Mass *a = masses[i];

		for (int j = 0; j < masses.size(); j++)
		{
			if (i == j)
				continue;

			Mass *b = masses[j];
			float dist = (b->pos - a->pos).lengthSquared();

			if (dist > max_dist_squared + scale / 100)
				continue;

			Spring *s = new Spring();
            s->k = 250;
			s->damp = 0.5f;
			s->x_rest = sqrt(dist);
			s->mass_1 = a;
			s->mass_2 = b;
			s->color = Vec3f(1, 0, 0);
			springs.push_back(s);
		}
	}

	// create faces
	float adj_dist_sq = scale * scale + 0.001f;  // distance of adjacent vertex
	for (int i = 0; i < masses.size(); i++)
	{
		Mass *a = masses[i];

		for (int j = i + 1; j < masses.size(); j++)
		{
			Mass *b = masses[j];

			float dist_sq_ba = (b->pos - a->pos).lengthSquared();

			if (dist_sq_ba > adj_dist_sq)
				continue;

			for (int k = j + 1; k < masses.size(); k++)
			{
				Mass *c = masses[k];

				float dist_sq_ca = (c->pos - a->pos).lengthSquared();

				if (dist_sq_ca > adj_dist_sq)
					continue;

				for (int n = k + 1; n < masses.size(); n++)
				{
					Mass *d = masses[n];

					float dist_sq_db = (d->pos - b->pos).lengthSquared();
					float dist_sq_dc = (d->pos - c->pos).lengthSquared();

					if (dist_sq_db > adj_dist_sq ||
						dist_sq_dc > adj_dist_sq)
						continue;

					Face f = Face(j, i, k);
					faces.push_back(f);
					f = Face(j, k, n);
					faces.push_back(f);
				}
			}
		}
	}

	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
		{
			Mass *m = &mass_heap[y * w + x];
			m->pos = start + Vec3f(x, -y, RAND_1() / 100) * scale;
		}

	//for (int i = 0; i < springs.size(); i++)
	//	springs[i]->load();

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	glGenBuffers(1, &vertBufferID);
	glGenBuffers(1, &normBufferID);

	verts.clear();
	normals.clear();

	updateGPU();
}

void Model5::update(float dt)
{
	Vec3f wind_force = (sin(time) + 1.5f) * Vec3f(1,0,0);
	time += dt;
	for (int i = 0; i < faces.size(); i++)
	{
		Mass *a = masses[faces[i].v_indices[0]];
		Mass *b = masses[faces[i].v_indices[1]];
		Mass *c = masses[faces[i].v_indices[2]];

		Vec3f norm = calcNormal(a->pos, b->pos, c->pos);		
		for (int j = 0; j < 3; j++)
			masses[faces[i].v_indices[j]]->force += abs(wind_force.dotProduct(norm)) * wind_force; // Vec3f(5, RAND_1() * 5, RAND_1() * 5);
	}

	Model::update(dt);
}

void Model5::updateGPU()
{
	//upload to gpu
	glBindBuffer(GL_ARRAY_BUFFER, vertBufferID);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vec3f) * verts.size(), // byte size of Vec3f, 3 of them
		verts.data(),      // pointer (Vec3f*) to contents of verts
		GL_STREAM_DRAW);   // Usage pattern of GPU buffer

	glEnableVertexAttribArray(0); // match layout # in shader
	glVertexAttribPointer(0,        // attribute layout # above
		3,        // # of components (ie XYZ )
		GL_FLOAT, // type of components
		GL_FALSE, // need to be normalized?
		0,        // stride
		(void *)0 // array buffer offset
	);

	glBindBuffer(GL_ARRAY_BUFFER, normBufferID);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vec3f) * normals.size(), // byte size of Vec3f, 3 of them
		normals.data(),      // pointer (Vec3f*) to contents of verts
		GL_STREAM_DRAW);   // Usage pattern of GPU buffer

	glEnableVertexAttribArray(1); // match layout # in shader
	glVertexAttribPointer(1,        // attribute layout # above
		3,        // # of components (ie XYZ )
		GL_FLOAT, // type of components
		GL_FALSE, // need to be normalized?
		0,        // stride
		(void *)0 // array buffer offset
	);
}

void Model5::render()
{
	verts.clear();
	normals.clear();

	for (int i = 0; i < faces.size(); i++)
	{
		Mass *a = masses[faces[i].v_indices[0]];
		Mass *b = masses[faces[i].v_indices[1]];
		Mass *c = masses[faces[i].v_indices[2]];

		verts.push_back(a->pos);
		verts.push_back(b->pos);
		verts.push_back(c->pos);

		Vec3f norm = calcNormal(a->pos, b->pos, c->pos);
		normals.push_back(norm);
		normals.push_back(norm);
		normals.push_back(norm);
	}
	//reloadColorUniform(color.x(), color.y(), color.z());

	// Use VAO that holds buffer bindings
	// and attribute config of buffers
	glBindVertexArray(vaoID);
	updateGPU();

	// Draw Quads, start at vertex 0, draw 4 of them (for a quad)
	glDrawArrays(GL_TRIANGLES, 0, verts.size());

	glBindVertexArray(0);
}

