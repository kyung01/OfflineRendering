#include "Easy_STD.h"
#include <fstream>
#include <iostream>

using namespace std;
Easy_STD::File Easy_STD::READ_FILE(char * path)
{
	const bool IS_PRINT = false;

	const int ARR_SIZE = 5000;
	char *arr_pointer = new char[ARR_SIZE];
	int n = 0;
	std::ifstream fin(path, std::ios::in);
	if (!fin.good()) {
		std::cout << "NOT GOOD" << std::endl;
		system("pause");
	}
	while (!fin.eof() && n < ARR_SIZE) {
		fin.get(arr_pointer[n++]);
	}
	if (IS_PRINT) {
		for (int i = 0; i < n; i++) {
			cout << arr_pointer[i];
		}
		cout << endl;
	}
	Easy_STD::File file{ unique_ptr<char>(arr_pointer),ARR_SIZE,n };
	return file;
}
