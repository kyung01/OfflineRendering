#pragma once
#include "glm\glm.hpp"
#include "glm\gtx\vector_angle.hpp"
#include "glm\gtc\matrix_transform.hpp"
using namespace glm;
namespace KGame {
	enum E_TYPE_MODEL { BUNNY, TEAPOT, CUBE, SPHERE };
	class Entity {
		void update_look();
	protected:
		E_TYPE_MODEL type_model;
		vec3 pos, scale, rotation, look;
	public:
		Entity();
		Entity(E_TYPE_MODEL type);
		vec3 get_pos();
		vec3 get_scale();
		vec3 get_rotation();
		Entity set_scale(float x, float y, float z);
		Entity set_pos(float x, float y, float z);
		Entity set_rotation(float x, float y, float z);
		virtual void update(float timeElapsed);
		E_TYPE_MODEL get_modelType();
		void cout();
		void lookAt(float x, float y, float z);
	};
}