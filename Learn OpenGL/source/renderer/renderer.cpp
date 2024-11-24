#include <iostream>
#include <format>
#include <string>

#include <glad/gl.h>

#include "renderer.hpp"

namespace Renderer {
	// const void* userParam is unused at the moment
	void GLAPIENTRY GL_ErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		std::string severity_str = "";
		switch (severity) {
			case GL_DEBUG_SEVERITY_LOW: severity_str = "LOW"; break;
			case GL_DEBUG_SEVERITY_MEDIUM: severity_str = "MEDIUM";  break;
			case GL_DEBUG_SEVERITY_HIGH: severity_str = "HIGH"; break;
			default: severity_str = "UNKNOWN"; break;
		}

		std::cout << std::format("[OPENGL ERROR] [{}] {} {} {} {} - '{}'", severity_str, source, type, id, length, message) << std::endl;
	}
}