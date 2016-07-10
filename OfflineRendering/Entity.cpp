#include "Entity.h"
#include <iostream>
using namespace KGame;
void KGame::Entity::update_look()
{
	mat4 mat;
	mat = glm::rotate<float>(mat, rotation.x, glm::vec3(1, 0, 0));
	mat = glm::rotate<float>(mat, rotation.y, glm::vec3(0, 1, 0));
	mat = glm::rotate<float>(mat, rotation.z, glm::vec3(0, 0, 1));
	vec4 lookNew =( mat * vec4(0, 0, 1,1));
	look = vec3(lookNew.x, lookNew.y, lookNew.z);
}

KGame::Entity::Entity():KGame::Entity(E_TYPE_MODEL::CUBE)
{
}

KGame::Entity::Entity(E_TYPE_MODEL type)
{
	this->type_model = type;
	this->scale = vec3(1, 1, 1);
	update_look();
}

vec3 KGame::Entity::get_pos()
{
	return this->pos;
}

vec3 KGame::Entity::get_scale()
{
	return this->scale;
}

vec3 KGame::Entity::get_rotation()
{
	return this->rotation;
}

Entity KGame::Entity::set_pos(float x, float y, float z)
{
	return *this;
}

Entity KGame::Entity::set_rotation(float x, float y, float z)
{
	this->rotation = vec3(x, y, z);
	update_look();
	return *this;
}

void KGame::Entity::update(float timeElapsed)
{
}

KGame::E_TYPE_MODEL KGame::Entity::get_modelType()
{
	return type_model;
}

void KGame::Entity::cout()
{
	std::cout << "Entity : " << type_model << std::endl;
	std::cout << "   pos     : " << pos.x << " " << pos.y << " " << pos.z << std::endl;
	std::cout << "   scale   : " << scale.x << " " << scale.y << " " << scale.z << std::endl;
	std::cout << "   rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;
	std::cout << "   look    : " << look.x << " " << look.y << " " << look.z << std::endl;
}

void KGame::Entity::lookAt(float x, float y, float z)
{
	vec3 dis = glm::normalize(glm::vec3(x, y, z) - this->pos);
	vec3 defaultAngle(0, 0, 1);
	float angle = glm::angle(defaultAngle, dis);
	vec3 axsOfRotation = glm::cross(defaultAngle, dis);
	float heading, attitude, bank;
	{
		float x = axsOfRotation.x, y = axsOfRotation.y, z = axsOfRotation.z;
		double s = sin(angle);
		double c = cos(angle);
		double t = 1 - c;
		//  if axis is not already normalised then uncomment this
		// double magnitude = Math.sqrt(x*x + y*y + z*z);
		// if (magnitude==0) throw error;
		// x /= magnitude;
		// y /= magnitude;
		// z /= magnitude;
		if ((x*y*t + z*s) > 0.998) { // north pole singularity detected
			heading = 2 * atan2(x*sin(angle / 2),cos(angle / 2));
			attitude = 3.14 / 2;
			bank = 0;
		}
		else if ((x*y*t + z*s) < -0.998) { // south pole singularity detected
			heading = -2 * atan2(x*sin(angle / 2), cos(angle / 2));
			attitude = -3.14 / 2;
			bank = 0;
		}
		else {
			heading = atan2(y * s - x * z * t, 1 - (y*y + z*z) * t);
			attitude = asin(x * y * t + z * s);
			bank = atan2(x * s - y * z * t, 1 - (x*x + z*z) * t);
		}
	}
	this->set_rotation(attitude, heading,bank);
}
