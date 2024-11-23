#include <iostream>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "renderer/renderer.hpp"
#include "renderer/shader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

class Application {
private:
	GLFWwindow* Window;
	GLuint VAO, VBO, EBO;
	Renderer::Shader* BasicShader;

public:
	Application() {
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->Window = glfwCreateWindow(800, 600, "Learn OpenGL 4.3", nullptr, nullptr);
		if (this->Window == nullptr) {
			std::cout << "GLFW Error: " << glfwGetError(nullptr) << "\n";
			exit(EXIT_FAILURE);
		}
		glfwMakeContextCurrent(this->Window);

		glfwSetFramebufferSizeCallback(this->Window, framebuffer_size_callback);

		int glad = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!glad) {
			std::cout << "Glad Error: " << "Init failed." << "\n";
			exit(EXIT_FAILURE);
		}

		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

		this->VAO = 0;
		this->VBO = 0;
		this->EBO = 0;

		this->BasicShader = nullptr;
	}

	~Application() {
		delete this->BasicShader;

		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);
		glDeleteVertexArrays(1, &this->VAO);

		glfwDestroyWindow(this->Window);
		glfwTerminate();
	}

	void Init() {
		GL_CALL(glViewport(0, 0, 800, 600));

		float vertices[] = {
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};
		unsigned int indices[] = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		// Vertex Array Object
		GL_CALL(glGenVertexArrays(1, &this->VAO));
		GL_CALL(glBindVertexArray(this->VAO));

		// Vertex Buffer Object
		GL_CALL(glGenBuffers(1, &this->VBO));
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->VBO));
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

		// Element Buffer Object
		GL_CALL(glGenBuffers(1, &this->EBO));
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO));
		GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

		this->BasicShader = new Renderer::Shader("shaders/basic.vert", "shaders/basic.frag");

		GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
		GL_CALL(glEnableVertexAttribArray(0));

		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GL_CALL(glBindVertexArray(0));
	}

	void Loop() {
		while (!glfwWindowShouldClose(this->Window)) {
			// Poll window events
			glfwPollEvents();

			// Update and check input
			ProcessInput(this->Window);

			// Rendering commands
			GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

			this->BasicShader->Use();
			this->BasicShader->SetUniform_vec4("COLOUR", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
			GL_CALL(glBindVertexArray(this->VAO));
			GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
			GL_CALL(glBindVertexArray(0));

			// Finish the frame by displaying the framebuffer
			glfwSwapBuffers(this->Window);
		}
	}
};

int main() {
	Application app;

	app.Init();
	app.Loop();

	return EXIT_SUCCESS;
}