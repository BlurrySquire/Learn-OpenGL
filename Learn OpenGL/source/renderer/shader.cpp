#include "shader.hpp"

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "renderer/renderer.hpp"

#include "system/file.hpp"

namespace Renderer {
	Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) {
		std::string vertex_source = System::ReadFile(vertex_path);
		std::string fragment_source = System::ReadFile(fragment_path);

		GLuint vertex_shader = this->CompileShader(vertex_source, GL_VERTEX_SHADER);
		GLuint fragment_shader = this->CompileShader(fragment_source, GL_FRAGMENT_SHADER);

		GL_CALL(this->ShaderProgram = glCreateProgram());
		GL_CALL(glAttachShader(this->ShaderProgram, vertex_shader));
		GL_CALL(glAttachShader(this->ShaderProgram, fragment_shader));
		GL_CALL(glLinkProgram(this->ShaderProgram));

		GL_CALL(glDeleteShader(vertex_shader));
		GL_CALL(glDeleteShader(fragment_shader));

		int  success;
		char infoLog[512];

		GL_CALL(glGetProgramiv(this->ShaderProgram, GL_LINK_STATUS, &success));
		if (!success) {
			GL_CALL(glGetProgramInfoLog(this->ShaderProgram, 512, nullptr, infoLog));
			std::cout << "ERROR::SHADER_PROGRAM::LINK_FAILED\n\t" << infoLog << std::endl;
		}
	}

	Shader::~Shader() {
		GL_CALL(glUseProgram(0));
		GL_CALL(glDeleteProgram(this->ShaderProgram));
	}

	GLuint Shader::CompileShader(const std::string& source, GLenum type) {
		GLuint shader;
		const GLchar* shader_source = source.c_str();

		GL_CALL(shader = glCreateShader(type));
		GL_CALL(glShaderSource(shader, 1, &shader_source, nullptr));
		GL_CALL(glCompileShader(shader));

		int success;
		char infoLog[512];

		GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
		if (!success) {
			GL_CALL(glGetShaderInfoLog(shader, 512, nullptr, infoLog));
			std::cout << "ERROR::SHADER::COMPILATION_FAILED\n\t" << infoLog << std::endl;
			return 0;
		}

		return shader;
	}

	void Shader::Use() {
		glUseProgram(this->ShaderProgram);
	}

	void Shader::SetUniform_int(const std::string& name, GLint value) {
		GL_CALL(GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str()));
		GL_CALL(glUniform1i(location, value));
	}

	void Shader::SetUniform_uint(const std::string& name, GLuint value) {
		GL_CALL(GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str()));
		GL_CALL(glUniform1ui(location, value));
	}

	void Shader::SetUniform_float(const std::string& name, GLfloat value) {
		GL_CALL(GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str()));
		GL_CALL(glUniform1f(location, value));
	}

	void Shader::SetUniform_vec2(const std::string& name, glm::vec2 value) {
		GL_CALL(GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str()));
		GL_CALL(glUniform2f(location, value[0], value[1]));
	}

	void Shader::SetUniform_vec3(const std::string& name, glm::vec3 value) {
		GL_CALL(GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str()));
		GL_CALL(glUniform3f(location, value[0], value[1], value[2]));
	}

	void Shader::SetUniform_vec4(const std::string& name, glm::vec4 value) {
		GL_CALL(GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str()));
		GL_CALL(glUniform4f(location, value[0], value[1], value[2], value[3]));
	}
}