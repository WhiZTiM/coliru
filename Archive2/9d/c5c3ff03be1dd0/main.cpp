#include <iostream>
#include <string>
#include <vector>

const char* utility::read_file(char* file_name) {
    std::ifstream file(file_name);
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	return content.c_str();
}