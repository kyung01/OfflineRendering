#include "Entity.h"

void KGame::Entity::update_look()
{
	mat4 mat;
	mat = glm::rotate<float>(mat, rotation.x, glm::vec3(1, 0, 0));
	mat = glm::rotate<float>(mat, rotation.y, glm::vec3(0, 1, 0));
	mat = glm::rotate<float>(mat, rotation.z, glm::vec3(0, 0, 1));
	look = mat * vec4(0, 0, 1, 1);
}

KGame::Entity::Entity()
{
	update_look();
}

void KGame::Entity::update(float timeElapsed)
{
}


