#pragma once
#include <memory>
class Easy_STD {
public:
	struct File {
		std::unique_ptr<char> array;
		int array_size;
		int array_used_size;
	};
	static File READ_FILE(char* path);
	static File READ_FILE02(char *arr, int arr_size, char* path);
};