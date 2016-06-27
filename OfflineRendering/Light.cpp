#include "Light.h"

int KGame::Light::ID_COUNT = 0;
KGame::Light::Light():id(ID_COUNT++)
{
}

int KGame::Light::get_id()
{
	return this->id;
}
