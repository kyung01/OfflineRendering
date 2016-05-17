#include "PlayerMovement.h"

PlayerMovement::PlayerMovement() :matRotations({
	{ FORWARD ,mat4() },
	{ BACKWARD,mat4() },
	{ LEFT,mat4() },
	{ RIGHT,mat4() } })
{
	std::cout << "PLAYERMOVEMENT CREATED\n";
	position = vec4(0, 0, 0, 1);
	dirForward = vec4(0, 0, 1, 1);

	matRotations.at(FORWARD)[0].w = 1;
	matRotations.at(FORWARD)[2].w = 1;
	matRotations.at(BACKWARD)[2].w = -1;
	matRotations.at(LEFT)[0].w = -1;
	matRotations.at(RIGHT)[0].w = 1;
	
}

void PlayerMovement::move(DIR_MOVEMENT dir, float power)
{
	position += vec4(0, 0, 0, 1) * matRotations[dir] * power;
	position.w = 1;
	std::cout << position.x << " " << position.y << " " << position.z << " " << position.w << std::endl;
	
}
float PlayerMovement::x()
{
	return position.x;
}

float PlayerMovement::y()
{
	return position.y;
}

float PlayerMovement::z()
{
	return position.z;
}
