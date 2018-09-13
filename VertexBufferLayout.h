#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType (unsigned int type) {
		if (type == GL_FLOAT) {
			return 4;
		} else if (type == GL_UNSIGNED_INT) {
			return 4;
		} else if (type == GL_UNSIGNED_BYTE) {
			return 1;
		}
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout () : m_Stride(0) {}

	/*template<typename T>
	void push (unsigned int count) {
		static_assert(false);
	}*/

	void pushFloat (unsigned int count) {
		m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	void pushUnsignedInt (unsigned int count) {
		m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	void pushUnsignedChar (unsigned int count) {
		m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const/*&*/ std::vector<VertexBufferElement> getElements () const { return m_Elements; }

	inline unsigned int getStride () const { return m_Stride; }
};