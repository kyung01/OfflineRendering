#pragma once
#include "GLFW\glfw3.h"
#include <list>
#include <map>
//check and fire event once the disgnated key is pressed
class GLFW_KeyChecker {
	__event void EVT_KEY_PRESSED(int key);
	std::list<int> keysPressed;
	std::map<int, int> mapKeyState;
public:
	void checkKey(int key, int keyState);


};