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
	{
		masses[i]->addGravity(dt);
		masses[i]->resolveForce(dt);
	}
}
