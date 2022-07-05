#include"VertexBuffer.h"

void VertexBuffer::vertexData(const std::string& arrayName) {
	std::fstream file;
	file.open("extras/objData/VertexData.txt", std::ios::in);
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
				data.push_back(atof(word.c_str()));
			}
			dObj.numLines++;
		}
	}
	for (GLuint i = 0, j = 0; i < 3; ++i) {
		GLsizei size = dObj.sections[dObj.sectionNames[i]];
		if (size != 0) {
			dObj.sectionSize.push_back(size);
		}
	}
}

VertexBuffer::VertexBuffer(const void* data, size_t size) {
	GLCall(glGenBuffers(1, &m_RendererId));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId))
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const std::string& arrayName) {
	vertexData(arrayName);
	GLCall(glGenBuffers(1, &m_RendererId));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
	GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
	GLCall(glDeleteBuffers(1, &m_RendererId));
}

GLuint VertexBuffer::getId() {
	return m_RendererId;
}

std::vector<GLsizei> VertexBuffer::getSectionSize() {
	return dObj.sectionSize;
}

void VertexBuffer::bind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::unbind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}