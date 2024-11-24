#ifndef RENDERER_SHADER_HPP
#define RENDERER_SHADER_HPP

#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace Renderer {
	class Shader {
	private:
		GLuint ShaderProgram;

		GLuint CompileShader(const std::string& source, GLenum type);
	public:
		Shader(const std::string& vertex_path, const std::string& fragment_path);
		~Shader();

		void Use();

		void SetUniform_int(const std::string& name, GLint value);
		void SetUniform_uint(const std::string& name, GLuint value);
		void SetUniform_float(const std::string& name, GLfloat value);
		void SetUniform_vec2(const std::string& name, glm::vec2 value);
		void SetUniform_vec3(const std::string& name, glm::vec3 value);
		void SetUniform_vec4(const std::string& name, glm::vec4 value);
	};
}

#endif