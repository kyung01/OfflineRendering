#pragma once
#include <list> // list to add all the drawable objects
#include "WorldObject.h"
#include "Entity.h"
#include "Light.h"
namespace KGame {
	class World {
		//std::list<WorldObject> objects;//all the objects in the world
		//WorldObject *worldCenterObject;//but one to follow around 
		Entity camera; 

	public:
		std::list<Light> lights;
		std::list<Entity> entities;
		World();
		void load_scene00();
		void update(float timeElapsed);
	};
}