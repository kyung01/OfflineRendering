#include "HPR.h"
#include <string>

string HPR::toString(glm::mat4x4 m)
{
	string s = "{\n";
	for (int i = 0; i < 4; i++) {
		s += " { ";
		for (int j = 0; j < 4; j++) {
			s += "";
			s += std::to_string (m[i][j]) ;
			if (j != 3) s += ", ";
		}
		s += " }\n";
		//std::cout << std::endl;
	}
	s += " }";

	return s;
}
