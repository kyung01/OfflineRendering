#include "PlayerMovement.h"
#include "glm\mat4x4.hpp"
#include "glm\gtx\transform.hpp"
PlayerMovement::PlayerMovement() :matRotations({
	{ FORWARD ,mat4() },
	{ BACKWARD,mat4() },
	{ LEFT,mat4() },
	{ RIGHT,mat4() } })
{
	std::cout << "PLAYERMOVEMENT CREATED\n";
	position = vec4(0, 0, 0, 1);
	dirForward = vec4(0, 0, 1, 1);
	dirSide = vec4(1, 0, 0, 1);
	dirUpward = vec4(0, 1, 0, 1);
	matRotations.at(FORWARD)[2].w = 1;
	matRotations.at(BACKWARD)[2].w = -1;
	matRotations.at(LEFT)[0].w = -1;
	matRotations.at(RIGHT)[0].w = 1;
	
}

void PlayerMovement::move(DIR_MOVEMENT dir, float power)
{
	map<int, float> mapDirRotationNeeded({ 
		{ DIR_MOVEMENT::FORWARD,0 },
		{ DIR_MOVEMENT::BACKWARD,0 } ,
		{ DIR_MOVEMENT::LEFT,90 } ,
		{ DIR_MOVEMENT::RIGHT,4.71 } });
	vec4 moved;
	if (dir == DIR_MOVEMENT::FORWARD) {
		moved = dirForward;
	}
	else if (dir == DIR_MOVEMENT::BACKWARD) {
		moved = -dirForward;
	}
	else if (dir == DIR_MOVEMENT::RIGHT) {
		moved = dirSide;
	}
	else if (dir == DIR_MOVEMENT::LEFT) {
		moved = -dirSide;
	}
	moved.w = 0;
	std::cout << moved.x << " " << moved.y << " " << moved.z << " " << moved.w << std::endl;
	position += moved * power;
	/**
	vec4 moved = vec4(0, 0, 0, 1) * matRotations[dir] * power;
	std::cout << moved.x << " " << moved.y << " " << moved.z << " " << moved.w << std::endl;
	//std::cout << position.x << " " << position.y << " " << position.z << " " << position.w << std::endl;
	position += vec4(0, 0, 0, 1) * matRotations[dir] * power;
	position.w = 1;
	*/
	
}
void PlayerMovement::rotateAxis(double changeX, double changeY)
{
	vec3 dirY = glm::cross(vec3(dirUpward.x, dirUpward.y, dirUpward.z) , vec3(dirForward.x, dirForward.y, dirForward.z));
	//mat4 rotationX = glm::rotate<float>(changeX, vec3(dirUpward.x, dirUpward.y, dirUpward.z));
	mat4 rotationX = glm::rotate<float>(changeX, vec3(dirUpward.x, dirUpward.y, dirUpward.z));
	mat4 rotationY = glm::rotate<float>(changeY, vec3(dirY.x, dirY.y, dirY.z));

	mat4 rotationMatrix = glm::rotate<float>(changeX, vec3(dirUpward.x, dirUpward.y, dirUpward.z));
	

	//dirForward = dirForward*rotationX; // x change
	dirForward = dirForward * rotationY*rotationX;
	dirSide = dirSide * rotationY*rotationX;;
	//dirUpward = dirUpward;// *rotationY;
	//cout << dirForward.x << " " << dirForward.y << " " << dirForward.z<< " " << dirForward.w << endl;
	//glm::simd(changeX)
}
vec3 PlayerMovement::getPosition()
{
	return  vec3(position.x, position.y, position.z);
}

vec3 PlayerMovement::getDirForward()
{
	return vec3(dirForward.x, dirForward.y, dirForward.z);
}

vec3 PlayerMovement::getDirUpward()
{
	return vec3(dirUpward.x, dirUpward.y, dirUpward.z);
}
