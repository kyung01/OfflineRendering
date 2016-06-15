#include "Porgram_Default.h"
#include <fstream>
int Program_Default::open_file(char * arr, int arr_size, const char * path)
{
	int n = 0;
	std::ifstream fin(path, std::ios::in);
	while (!fin.eof() && n < arr_size ) {
		fin.get(arr[n++]);
	}

	return 0;
}

Program_Default::Program_Default()
{
}

bool Program_Default::init(const char * path_vert, const char * path_frag)
{
	return false;
}
