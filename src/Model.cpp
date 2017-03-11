#include "Model.h"

void Model::render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->render();
}

void Model::init()
{
}

void Model::update(float dt)
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->update(dt);
}

void Model1::init() 
{
	objects.push_back(new Spring());

	for (int i = 0; i < objects.size(); i++)
		objects[i]->load();
		
}