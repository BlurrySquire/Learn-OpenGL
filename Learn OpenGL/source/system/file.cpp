#include "file.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

namespace System {
	std::string ReadFile(const std::string& file_path) {
		std::ifstream file(file_path);
		if (file.is_open()) {
			std::stringstream buffer;
			buffer << file.rdbuf();
			return buffer.str();
		}
		else {
			std::cout << "ERROR::FILE::READ::UNABLE_TO_READ\n\t";
			std::cout << "'" << file_path << "'" << std::endl;
			return "\0";
		}
	}
}