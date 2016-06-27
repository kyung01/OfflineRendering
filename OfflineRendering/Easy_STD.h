#pragma once
;
class Easy_STD {
public:
	struct File {
		char * array;
		int array_size;
		int array_used_size;
	};
	static int READ_FILE(char *arr, int arr_size, char* path);
	static File READ_FILE02(char *arr, int arr_size, char* path);
};