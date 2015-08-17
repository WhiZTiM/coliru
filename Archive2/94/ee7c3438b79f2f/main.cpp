#include <iostream>
#include <string>
#include <vector>

std::string utility::read_file(const char* file_name) {
    std::ifstream file(file_name);
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	return content;
}

const char* vertex_shader_source = utility::read_file("vertex_shader.txt").c_str();
printf(vertex_shader_source); // memory is freed?
printf(utility::read_file("vertex_shader.txt").c_str()); // prints out what I want