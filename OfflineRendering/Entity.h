#pragma once
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
using namespace glm;
namespace KGame {
	class Entity {
		void update_look();
	protected:
		enum E_TYPE_MODEL {RABBIT, TEAPOT,CUBE,SPHERE };
		E_TYPE_MODEL type_model;
		vec4 pos, scale, rotation, look;
	public:
		Entity();
		Entity set_scale(float x, float y, float z);
		Entity set_pos(float x, float y, float z);
		Entity set_rotation(float x, float y, float z);
		virtual void update(float timeElapsed);
	};
}