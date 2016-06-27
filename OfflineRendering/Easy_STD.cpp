#include "Easy_STD.h"
#include <fstream>
#include <iostream>

int Easy_STD::READ_FILE(char * arr, int arr_size, char * path)
{
	int n = 0;
	std::ifstream fin(path, std::ios::in);
	if (!fin.good()) {
		std::cout << "NOT GOOD" << std::endl;
		system("pause");
	}
	while (!fin.eof() && n < arr_size) {
		fin.get(arr[n++]);
	}

	return n;
}
