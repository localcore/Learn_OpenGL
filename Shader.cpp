#include <string>
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include "Renderer.h"
#include "Shader.h"

Shader::Shader (const std::string& filepath) : m_FilePath(filepath), m_RendererID(0) {
	ShaderProgramSource source = parseShader(filepath);
	m_RendererID = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader () {
	glDeleteProgram(m_RendererID);
}

void Shader::bind () const {
	glUseProgram(m_RendererID);
}

void Shader::unbind () const {
	glUseProgram(0);
}

void Shader::setUniform1i (const std::string& name, int v) {
	glUniform1i(getUniformLocation(name), v);
}

void Shader::setUniform1f (const std::string& name, float v) {
	glUniform1f(getUniformLocation(name), v);
}

void Shader::setUniform4f (const std::string& name, float v0, float v1, float v2, float v3) {
	glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

int Shader::getUniformLocation (const std::string& name) {
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
		return m_UniformLocationCache[name];
	}
	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1) {
		std::cout << "Warning uniform '" << name << "' doesn't exist!\n";
	}
	m_UniformLocationCache[name] = location;
	return location;
}

ShaderProgramSource Shader::parseShader (const std::string& filepath) {
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

unsigned int Shader::compileShader (unsigned int type, const std::string& source) {
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

unsigned int Shader::createShader (const std::string& vertexSha, const std::string& fragmentSha) {
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
