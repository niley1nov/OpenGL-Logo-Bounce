#include"VertexArray.h"

VertexArray::VertexArray() : m_index(0) {
	GLCall(glGenVertexArrays(1, &m_RendererId));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_RendererId));
}

void VertexArray::addBufferAndLayout(const VertexBuffer& vb, const VertexBufferLayout& vl) {
	bind();
	const auto& elements = vl.getElements();
	GLuint ptr = 0;
	vb.bind();
	for (GLuint i = 0; i < elements.size(); ++i) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(m_index));
		GLCall(glVertexAttribPointer(m_index, element.count, element.type, element.norm, vl.getStride(), (void*)ptr));
		ptr += element.count * sizeof(element.type);
		++m_index;
	}
}

GLuint VertexArray::getId() {
	return m_RendererId;
}

void VertexArray::bind() const {
	GLCall(glBindVertexArray(m_RendererId));
}

void VertexArray::unbind() const {
	GLCall(glBindVertexArray(0));
}