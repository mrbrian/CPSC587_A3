#include "Model.h"

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
		springs[i]->update(dt);
}

void Model1::init()
{
	Mass *m = new Mass();
	m->mass = 1;
	m->pos = new Vec3f(0, -2.5f, 0);
	m->vel = Vec3f(0, 0, 0);

	Spring *s = new Spring();
	s->pos = new Vec3f(0, -1.0f, 0);
	s->k = 1;
	s->x_rest = 1;
	s->mass = m;
	s->color = Vec3f(1, 0, 0);
	s->vel = Vec3f(0, 0, 0);

	springs.push_back(s);

	for (int i = 0; i < springs.size(); i++)
		springs[i]->load();
}

void Model2::init()
{
	Mass *m = new Mass();
	m->mass = 1;
	m->pos = new Vec3f(0, -3.0f, 0);
	m->vel = Vec3f(0, 0, 0);

	Spring *s2 = new Spring();
	s2->k = 1;
	s2->x_rest = 1;
	s2->mass = m;
	s2->color = Vec3f(0, 1, 0);
	s2->pos = new Vec3f(0, -1.5f, 0);
	s2->vel = Vec3f(0, 0, 0);

	Spring *s = new Spring();
	s->pos = new Vec3f(0, 0, 0);
	s->k = 1;
	s->x_rest = 1;
	s->mass = s2;
	s->color = Vec3f(1, 0, 0);
	s2->vel = Vec3f(0, 0, 0);

	springs.push_back(s);
	springs.push_back(s2);

	for (int i = 0; i < springs.size(); i++)
		springs[i]->load();

}