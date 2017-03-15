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
		springs[i]->applyForce(dt);

	for (int i = 0; i < masses.size(); i++)
		masses[i]->resolveForce(dt);
}

void Model1::init()
{
	Mass *m_1 = new Mass();
	m_1->mass = 1;
	m_1->pos = Vec3f(0, -1.0f, 0);
	m_1->vel = Vec3f(0, 0, 0);
	m_1->fixed = true;

	Mass *m_2 = new Mass();
	m_2->mass = 1;
	m_2->pos = Vec3f(0, -2.5f, 0);
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
	Mass *m_1 = new Mass();
	m_1->mass = 1;
	m_1->pos = Vec3f(0, 0, 0);
	m_1->vel = Vec3f(0, 0, 0);
	m_1->fixed = true;

	Mass *m_2 = new Mass();
	m_2->mass = 1;
	m_2->pos = Vec3f(0, -1.0f, 0);
	m_2->vel = Vec3f(0, 0, 0);

	Mass *m_3 = new Mass();
	m_3->mass = 1;
	m_3->pos = Vec3f(1, -3.0f, 0);
	m_3->vel = Vec3f(0, 0, 0);

	Spring *s = new Spring();
	s->k = 10;
	s->damp = 1.0f;
	s->x_rest = 1;
	s->mass_1 = m_1;
	s->mass_2 = m_2;
	s->color = Vec3f(1, 0, 0);

	Spring *s2 = new Spring();
	s2->k = 10;
	s2->damp = 1.0f;
	s2->x_rest = 1;
	s2->mass_1 = m_2;
	s2->mass_2 = m_3;
	s2->color = Vec3f(0, 1, 0);

	springs.push_back(s);
	springs.push_back(s2);
	masses.push_back(m_1);
	masses.push_back(m_2);
	masses.push_back(m_3);

	for (int i = 0; i < springs.size(); i++)
		springs[i]->load();

}