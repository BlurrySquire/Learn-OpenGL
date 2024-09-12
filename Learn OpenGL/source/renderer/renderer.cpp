#include <iostream>

#include <glad/glad.h>

#include "renderer.hpp"

namespace Renderer {
	void GL_ClearErrors() {
		while (glGetError() != GL_NO_ERROR) {
		}
	}

	void GL_LogError(const char* function, const char* file, const int line) {
		while (GLenum error = glGetError()) {
			std::cout << "ERROR::OPENGL " << error << "\n\t";
			std::cout << "In '" << function << "'";
			std::cout << " in " << "'" << file << "'";
			std::cout << " at line " << line << "\n\t";
		}
	}
}