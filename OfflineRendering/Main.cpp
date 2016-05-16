#include "Main.h"

bool main() {
	EasyGLFW myGLFW = EasyGLFW();
	myGLFW.init(500,500,"hi");
	myGLFW.startLoop();

	std::cout << "SystemEnding...\n";
	system("pause");
}