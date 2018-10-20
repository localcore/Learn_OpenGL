#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

class Renderer {
public:
	void clear () const;

	void draw (const VertexArray&, const IndexBuffer&, const Shader&) const;
};