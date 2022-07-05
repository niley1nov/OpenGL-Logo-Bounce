#include"IndexBuffer.h"

void IndexBuffer::indexData(const std::string& arrayName) {
	std::fstream file;
	file.open("extras/objData/IndexData.txt", std::ios::in);
	if (file.fail()) {
		std::cout << "Vertex data file didn't open" << std::endl;
		file.clear();
	}
	std::string line;
	GLboolean flag = GL_FALSE; // objData
	while (std::getline(file, line)) {
		if (line.find(("~" + arrayName).c_str()) != std::string::npos) {
			flag = GL_TRUE;
		}
		else if (flag && line.find("#") != std::string::npos) {
			std::string word;
			std::stringstream ss(line);
			while (ss >> word) {
				dObj.sections[word]++;
			}
		}
		else if (flag && line.find("~") != std::string::npos) {
			break;
		}
		else {
			std::string word;
			std::stringstream ss(line);
			while (ss >> word) {
				data.push_back(std::stoul(word.c_str()));
			}
			dObj.numLines++;
		}
	}
	dObj.sectionSize = dObj.sections[dObj.sectionName];
	m_count = dObj.sectionSize * dObj.numLines;
}

IndexBuffer::IndexBuffer(const GLuint* data, GLuint count) :m_count(count) {
	GLCall(glGenBuffers(1, &m_RendererId));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(GLuint), data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(const std::string& arrayName) {
	indexData(arrayName);
	GLCall(glGenBuffers(1, &m_RendererId));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(GLuint), &data[0], GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
	GLCall(glDeleteBuffers(1, &m_RendererId));
}

GLuint IndexBuffer::getId() {
	return m_RendererId;
}

void IndexBuffer::bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void IndexBuffer::unbind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}