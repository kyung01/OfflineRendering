#pragma once
#include "Entity.h"
namespace KGame {
	class Light : public Entity {
		static int ID_COUNT;
	protected:
		enum E_TYPE_LIGHT { DIRECTIONAL, SPOTLIGHT, BALL };
		int id;
		E_TYPE_LIGHT type_light;
		float brightness; // how far the light bean reaches
	public:
		Light();
		int get_id();
	};
}