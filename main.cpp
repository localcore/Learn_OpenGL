#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
//#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

void processInput (GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback (GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

GLFWwindow* createWindow ();

int main (int argc, char* argv[]) {

	GLFWwindow* window = createWindow();

	/*float vertices[] = {
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f, 0.5f,

			0.5f, 0.5f,
			-0.5f, 0.5f,
			-0.5f, -0.5f,

			-0.5f, -0.5f,
			0.0f, -0.8f,
			0.5f, -0.5f,
	};*/

	float positions[] = {
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f, 0.5f,
			-0.5f, 0.5f,
	};

	unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,
	};

	VertexArray va;
	VertexBuffer vb(positions, sizeof(positions));

	VertexBufferLayout layout;
	layout.pushFloat(2);
	va.addBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	Shader shader("res/shaders/triangle.glsl");
	shader.bind();


	va.unbind();
	vb.unbind();
	ib.unbind();
	shader.unbind();

	float r = 1.0f;
	float increment = 0.05f;

	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);

		shader.bind();
		shader.setUniform4f("u_Color", r, 0.0f, 0.0f, 1.0f);

		va.bind();
		ib.bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);

		r += increment;
		if (r >= 1 or r <= 0) {
			if (increment > 0) {
				r = 1;
			} else {
				r = 0;
			};
			increment = -increment;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shader.~Shader();

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