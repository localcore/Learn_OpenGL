#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer {
public:
	void clear () const;

	void draw (const VertexArray&, const IndexBuffer&, const Shader&) const;
};