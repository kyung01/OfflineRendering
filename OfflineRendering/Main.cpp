#include "Main.h"
#include "glm\glm.hpp"
#include <map>
bool main() {
	
	EasyGLFW myGLFW;
	myGLFW.init(500,500,"hi");
	myGLFW.startLoop();

	std::cout << "SystemEnding...\n";
	return true;
	//system("pause");
}