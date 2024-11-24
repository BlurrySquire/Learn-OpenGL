#include "shader.hpp"

#include <iostream>
#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "renderer/renderer.hpp"

#include "system/file.hpp"

namespace Renderer {
	Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) {
		std::string vertex_source = System::ReadFile(vertex_path);
		std::string fragment_source = System::ReadFile(fragment_path);

		GLuint vertex_shader = this->CompileShader(vertex_source, GL_VERTEX_SHADER);
		GLuint fragment_shader = this->CompileShader(fragment_source, GL_FRAGMENT_SHADER);

		this->ShaderProgram = glCreateProgram();
		glAttachShader(this->ShaderProgram, vertex_shader);
		glAttachShader(this->ShaderProgram, fragment_shader);
		glLinkProgram(this->ShaderProgram);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		int  success;
		char infoLog[512];

		glGetProgramiv(this->ShaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->ShaderProgram, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER_PROGRAM::LINK_FAILED\n\t" << infoLog << std::endl;
		}
	}

	Shader::~Shader() {
		glUseProgram(0);
		glDeleteProgram(this->ShaderProgram);
	}

	GLuint Shader::CompileShader(const std::string& source, GLenum type) {
		GLuint shader;
		const GLchar* shader_source = source.c_str();

		shader = glCreateShader(type);
		glShaderSource(shader, 1, &shader_source, nullptr);
		glCompileShader(shader);

		int success;
		char infoLog[512];

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::COMPILATION_FAILED\n\t" << infoLog << std::endl;
			return 0;
		}

		return shader;
	}

	void Shader::Use() {
		glUseProgram(this->ShaderProgram);
	}

	void Shader::SetUniform_int(const std::string& name, GLint value) {
		GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str());
		glUniform1i(location, value);
	}

	void Shader::SetUniform_uint(const std::string& name, GLuint value) {
		GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str());
		glUniform1ui(location, value);
	}

	void Shader::SetUniform_float(const std::string& name, GLfloat value) {
		GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str());
		glUniform1f(location, value);
	}

	void Shader::SetUniform_vec2(const std::string& name, glm::vec2 value) {
		GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str());
		glUniform2f(location, value[0], value[1]);
	}

	void Shader::SetUniform_vec3(const std::string& name, glm::vec3 value) {
		GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str());
		glUniform3f(location, value[0], value[1], value[2]);
	}

	void Shader::SetUniform_vec4(const std::string& name, glm::vec4 value) {
		GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str());
		glUniform4f(location, value[0], value[1], value[2], value[3]);
	}
}