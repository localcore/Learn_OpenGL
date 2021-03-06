#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.h"

GLFWwindow* createWindow ();

void framebuffer_size_callback (GLFWwindow*, int, int);

void processInput (GLFWwindow*);

int main (int argc, char* argv[]) {

	GLFWwindow* window = createWindow();

	{

		float positions[] = {
				-100.0f, -100.0f, 0.0f, 0.0f,
				100.0f, -100.0f, 1.0f, 0.0f,
				100.0f, 100.0f, 1.0f, 1.0f,
				-100.0f, 100.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0,
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		VertexArray va;
		VertexBuffer vb(positions, sizeof(positions));

		VertexBufferLayout layout;
		layout.pushFloat(2);
		layout.pushFloat(2);
		va.addBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1), glm::vec3(640, 360, 0));

		Shader shader("res/shaders/triangle.glsl");

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

			if (r > 1 or r < 0)
				increment = -increment;
			r += increment;

			{
				glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(r * 200, 0, 0));
				glm::mat4 mvp = proj * view * model;
				shader.setUniformMat4f("u_MVP", mvp);
				renderer.draw(va, ib, shader);
			}

			{
				glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(0, r * 300, 0));
				glm::mat4 mvp = proj * view * model;
				shader.setUniformMat4f("u_MVP", mvp);
				renderer.draw(va, ib, shader);
			}

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

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Learn OpenGL", nullptr, nullptr);
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