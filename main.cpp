#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

GLFWwindow* createWindow ();

void framebuffer_size_callback (GLFWwindow*, int, int);

void processInput (GLFWwindow*);

int main (int argc, char* argv[]) {

	GLFWwindow* window = createWindow();

	float positions[] = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,
	};

	{

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		VertexArray va;
		VertexBuffer vb(positions, sizeof(positions));

		VertexBufferLayout layout;
		layout.pushFloat(2);
		layout.pushFloat(2);
		va.addBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

		Shader shader("res/shaders/triangle.glsl");
		shader.bind();

		Texture texture("res/textures/prova.png");
		texture.bind(0);
		shader.setUniform1i("u_Texture", 0);

		va.unbind();
		vb.unbind();
		ib.unbind();
		shader.unbind();

		Renderer renderer;

		float r = 0.0f;
		float increment = 0.05f;

		while (!glfwWindowShouldClose(window)) {

			processInput(window);
			renderer.clear();

			shader.bind();
			//shader.setUniform4f("u_Color", r, 0.0f, 0.0f, 1.0f);
			renderer.draw(va, ib, shader);

			if (r > 1 or r < 0)
				increment = -increment;
			r += increment;

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}

	glfwTerminate();
	return 0;
}

GLFWwindow* createWindow () {

	if (!glfwInit()) {
		return nullptr;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);

	if (!window) {
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}
	return window;
}

void framebuffer_size_callback (GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput (GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}