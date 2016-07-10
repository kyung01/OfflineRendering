#include "World.h"

KGame::World::World()
{
}

void KGame::World::load_scene00()
{
	Entity rabbit(E_TYPE_MODEL::BUNNY);
	this->entities.push_back(rabbit);

	this->camera.set_pos(1, 1, 1);
}

void KGame::World::update(float timeElapsed)
{
}
