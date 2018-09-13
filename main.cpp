#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>

#include "Renderer.h"
//#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

void processInput (GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback (GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

static ShaderProgramSource parseShader (const std::string& filepath) {
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			} else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		} else {
			ss[(int) type] << line << '\n';
		}
	}
	return {ss[0].str(), ss[1].str()};
}

static unsigned int compileShader (unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char message[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
		std::cout << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

static unsigned int createShader (const std::string& vertexSha, const std::string& fragmentSha) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexSha);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentSha);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
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

	ShaderProgramSource source = parseShader("res/shaders/triangle.glsl");
	unsigned int shader = createShader(source.vertexSource, source.fragmentSource);
	glUseProgram(shader);

	int location = glGetUniformLocation(shader, "u_Color");

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	float r = 1.0f;
	float increment = 0.05f;

	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);
		glUniform4f(location, r, 0.0f, 0.0f, 1.0f);

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

	//glDeleteProgram(shader);

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