#include"UniformBuffer.h"

GLuint UniformBuffer::calcSize(GLuint index) {
	GLuint size = 0;
	for (GLuint i = 0; i < index; ++i) {
		size += slots[i];
	}
	return size;
}

UniformBuffer::UniformBuffer() {}

UniformBuffer::~UniformBuffer() {
	GLCall(glDeleteBuffers(1, &m_RendererId));
}

void UniformBuffer::push(GLuint count, GLuint size) {
	for (GLuint i = 0; i < count; ++i) {
		slots.push_back(size);
	}
}

void UniformBuffer::buildBuffer(GLuint index, GLenum usage) {
	GLCall(glGenBuffers(1, &m_RendererId));
	bind();
	GLuint size = calcSize(slots.size());
	GLCall(glBufferData(GL_UNIFORM_BUFFER, size, NULL, usage));
	unbind();
	GLCall(glBindBufferRange(GL_UNIFORM_BUFFER, index, m_RendererId, 0, size));
}

void UniformBuffer::fillData(const GLuint& slotNum, const void* data) {
	GLCall(glBufferSubData(GL_UNIFORM_BUFFER, calcSize(slotNum), slots[slotNum], data));
}

void UniformBuffer::bind() const {
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_RendererId));
}

void UniformBuffer::unbind() const {
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}