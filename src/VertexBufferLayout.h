#pragma once

#include"Renderer.h"

struct LayoutElement {
	GLenum type;
	GLint count;
	GLboolean norm;
};

class VertexBufferLayout {
private:
	std::vector<LayoutElement> m_Elements;
	GLsizei m_Stride;

public:
	VertexBufferLayout();
	~VertexBufferLayout();

	template<typename T>
	void push(GLint);

	inline const std::vector<LayoutElement>& getElements() const { return m_Elements; }
	inline GLuint getStride() const { return m_Stride; }
};