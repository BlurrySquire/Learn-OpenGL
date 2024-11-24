#include <iostream>
#include <string>

#include <glad/gl.h>
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

		#ifdef _DEBUG
			glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
		#endif

		this->Window = glfwCreateWindow(800, 600, "Learn OpenGL 4.3", nullptr, nullptr);
		if (this->Window == nullptr) {
			std::cout << "GLFW Error: " << glfwGetError(nullptr) << "\n";
			exit(EXIT_FAILURE);
		}
		glfwMakeContextCurrent(this->Window);

		glfwSetFramebufferSizeCallback(this->Window, framebuffer_size_callback);

		int glad = gladLoadGL((GLADloadfunc)glfwGetProcAddress);
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
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glDebugMessageCallback(Renderer::GL_ErrorCallback, 0);

		glViewport(0, 0, 800, 600);

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
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		// Vertex Buffer Object
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Element Buffer Object
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		this->BasicShader = new Renderer::Shader("shaders/basic.vert", "shaders/basic.frag");

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Loop() {
		while (!glfwWindowShouldClose(this->Window)) {
			// Poll window events
			glfwPollEvents();

			// Update and check input
			ProcessInput(this->Window);

			// Rendering commands
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			this->BasicShader->Use();
			this->BasicShader->SetUniform_vec4("COLOUR", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
			glBindVertexArray(this->VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

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