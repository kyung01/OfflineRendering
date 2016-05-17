#pragma once
#include <glm\vec4.hpp>
#include <glm\mat4x4.hpp>
#include <map>
#include <iostream>
#include "HPR.h"
using namespace glm;

class PlayerMovement {
	vec4 position;
	vec4 dirForward;
	mat4 matForward;
	std::map<int, mat4> matRotations; // contain direction changs 
public :
	enum DIR_MOVEMENT : int {FORWARD,BACKWARD,LEFT,RIGHT};
	PlayerMovement();
	void move(DIR_MOVEMENT dir, float power);
	float x();
	float y();
	float z();
	
};