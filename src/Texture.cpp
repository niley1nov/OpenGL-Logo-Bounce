#include"Texture.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#endif

Texture::Texture(const std::string& location, const GLenum& wrap) : m_LocalBuffer(nullptr) {
	GLCall(glGenTextures(1, &m_RendererId));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	stbi_set_flip_vertically_on_load(true);
	m_LocalBuffer = stbi_load(("extras/textures/" + location).c_str(), &width, &height, &nrChannels, 4);
	if (m_LocalBuffer) {
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else {
		std::cout << "Failed to load Texture!" << std::endl;
	}
	unbind();

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture() {
	GLCall(glDeleteTextures(1, &m_RendererId));
}

void Texture::bind(GLuint count) {
	GLCall(glActiveTexture(GL_TEXTURE0 + count));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));
}

void Texture::unbind() {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

GLuint Texture::getId() {
	return m_RendererId;
}