#pragma once

#include"Renderer.h"

class IndexBuffer {
private:
	struct aData {
	public:
		GLuint numLines;
		GLsizei sectionSize;
		std::map<std::string, GLuint> sections;
		std::string sectionName;
		aData() {
			sectionName = "#ind";
			numLines = 0;
			sections.insert(std::pair<std::string, GLuint>(sectionName, 0));
		}
	};
	GLuint m_RendererId, m_count;
	aData dObj;
	std::vector<GLuint> data;
	void indexData(const std::string&);

public:
	IndexBuffer(const GLuint*, GLuint);
	IndexBuffer(const std::string&);
	~IndexBuffer();
	GLuint getId();
	void bind() const;
	void unbind() const;
	
	inline GLuint getCount() const { return m_count; }
};