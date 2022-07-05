#pragma once

#include"Renderer.h"

class Texture {
private:
	GLuint m_RendererId;
	GLint width, height, nrChannels;
	GLubyte* m_LocalBuffer;

public:
	Texture(const std::string&, const GLenum&);
	~Texture();
	void bind(GLuint);
	void unbind();
	GLuint getId();
};