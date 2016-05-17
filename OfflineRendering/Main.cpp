#include "Main.h"

#include "EasyGLFW.h"
bool main() {
	
	EasyGLFW myGLFW;
	myGLFW.init(500,500,"hi");
	myGLFW.startLoop();

	std::cout << "SystemEnding...\n";
	return true;
	//system("pause");
}