#include"VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout() :m_Stride(0) {}

VertexBufferLayout::~VertexBufferLayout() {}

template<typename T>
void VertexBufferLayout::push(GLint count) {
	ASSERT(false);
}

template<> void VertexBufferLayout::push<GLfloat>(GLint count) {
	m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
	m_Stride += count * sizeof(GLfloat);
}

template<> void VertexBufferLayout::push<GLuint>(GLint count) {
	m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
	m_Stride += count * sizeof(GLuint);
}

template<> void VertexBufferLayout::push<GLubyte>(GLint count) {
	m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
	m_Stride += count * sizeof(GLubyte);
}