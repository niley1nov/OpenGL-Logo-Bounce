#pragma once

#include"Renderer.h"

class VertexBuffer {
private:
	struct aData {
	public:
		GLuint numLines;
		std::vector<GLsizei> sectionSize;
		std::map<std::string, GLuint> sections;
		std::vector<std::string> sectionNames;
		aData() {
			sectionNames.push_back("#pos");
			sectionNames.push_back("#norm");
			sectionNames.push_back("#tex");
			numLines = 0;
			sections.insert(std::pair<std::string, GLuint>(sectionNames[0], 0));
			sections.insert(std::pair<std::string, GLuint>(sectionNames[1], 0));
			sections.insert(std::pair<std::string, GLuint>(sectionNames[2], 0));
		}
	};
	GLuint m_RendererId;
	aData dObj;
	std::vector<GLfloat> data;
	void vertexData(const std::string&);

public:
	VertexBuffer(const void*, size_t);
	VertexBuffer(const std::string&);
	~VertexBuffer();
	GLuint getId();
	std::vector<GLsizei> getSectionSize();
	void bind() const;
	void unbind() const;
};