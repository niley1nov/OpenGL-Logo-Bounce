#pragma once

#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexBufferLayout.h"

class VertexArray {
private:
	GLuint m_RendererId, m_index;

public:
	VertexArray();
	~VertexArray();
	void addBufferAndLayout(const VertexBuffer&, const VertexBufferLayout&);
	GLuint getId();
	void bind() const;
	void unbind() const;
};