#pragma once

#include <iostream>
#include <unordered_map>

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader {
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader (const std::string&);

	~Shader ();

	void bind () const;

	void unbind () const;

	void setUniform1i (const std::string&, int);

	void setUniform1f (const std::string&, float);

	void setUniform4f (const std::string&, float, float, float, float);

private:
	ShaderProgramSource parseShader (const std::string&);

	unsigned int compileShader (unsigned int, const std::string&);

	unsigned int createShader (const std::string&, const std::string&);

	int getUniformLocation (const std::string&);
};