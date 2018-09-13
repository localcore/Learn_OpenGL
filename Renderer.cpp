#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.h"

void Renderer::clear () const {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw (const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
	shader.bind();
	//shader.setUniform4f("u_Color", r, 0.0f, 0.0f, 1.0f);
	va.bind();
	ib.bind();

	glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}
