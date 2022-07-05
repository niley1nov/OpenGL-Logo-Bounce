#pragma once

#include"Renderer.h"

class UniformBuffer {
private:
	GLuint m_RendererId;
	std::vector<GLuint> slots;
	GLuint calcSize(GLuint);

public:
	UniformBuffer();
	~UniformBuffer();
	void push(GLuint, GLuint);
	void buildBuffer(GLuint, GLenum);
	void fillData(const GLuint&, const void*);
	void bind() const;
	void unbind() const;
};