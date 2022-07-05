#include"Shader.h"

Shader::Shader() {
	shaderNames.insert(std::pair<GLenum, std::string>(GL_VERTEX_SHADER, "vertex"));
	shaderNames.insert(std::pair<GLenum, std::string>(GL_TESS_CONTROL_SHADER, "tess_control"));
	shaderNames.insert(std::pair<GLenum, std::string>(GL_TESS_EVALUATION_SHADER, "tess_eval"));
	shaderNames.insert(std::pair<GLenum, std::string>(GL_GEOMETRY_SHADER, "geometry"));
	shaderNames.insert(std::pair<GLenum, std::string>(GL_FRAGMENT_SHADER, "fragment"));
}

void Shader::gl_checkCompileErrors(GLuint id, const std::string& name) {
	if (name != "program") {
		int result;
		GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE) {
			int length;
			GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)alloca(length * sizeof(char));
			GLCall(glGetShaderInfoLog(id, length, &length, message));
			std::cout << "Failed to compile " << name << " shader!" << std::endl;
			std::cout << message << std::endl;
			GLCall(glDeleteShader(id));
		}
	}
	else {
		int result;
		GLCall(glGetProgramiv(id, GL_LINK_STATUS, &result));
		if (result == GL_FALSE) {
			int length;
			GLCall(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)alloca(length * sizeof(char));
			GLCall(glGetProgramInfoLog(id, length, &length, message));
			std::cout << "Failed to link program!" << std::endl;
			std::cout << message << std::endl;
			GLCall(glDeleteProgram(id));
		}
	}
}

void Shader::copyShader(GLuint Id) {
	m_RendererId = Id;
}

void Shader::push(GLenum shaderType, const std::string& shaderPath) {
	std::fstream shaderFile;
	std::string shaderCode;

	shaderFile.exceptions(std::istream::failbit | std::istream::badbit);
	try {
		shaderFile.open(("extras/shaders/" + shaderPath).c_str(), std::ios::in);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderCode = shaderStream.str();
		shaderFile.close();
	}
	catch(std::ifstream::failure e) {
		std::cout << "Error::Can not open shader file" << std::endl;
	}
	const char* source = shaderCode.c_str();
	GLuint shaderId;
	shaderId = glCreateShader(shaderType);
	GLCall(glShaderSource(shaderId, 1, &source, NULL));
	GLCall(glCompileShader(shaderId));
	gl_checkCompileErrors(shaderId, shaderNames[shaderType]);
	shaderIds.insert(std::pair<GLenum, GLuint>(shaderType, shaderId));
}

void Shader::buildShader() {
	m_RendererId = glCreateProgram();
	std::map<GLenum, GLuint>::iterator it = shaderIds.begin();
	while (it != shaderIds.end()) {
		GLCall(glAttachShader(m_RendererId, it->second));
		++it;
	}
	GLCall(glLinkProgram(m_RendererId));
	GLCall(glValidateProgram(m_RendererId));
	gl_checkCompileErrors(m_RendererId, "program");
	it = shaderIds.begin();
	while (it != shaderIds.end()) {
		GLCall(glDeleteShader(it->second));
		++it;
	}
}

GLuint Shader::getId() {
	return m_RendererId;
}

void Shader::use() {
	GLCall(glUseProgram(m_RendererId));
}

GLuint Shader::getUniformLoc(const std::string& name) const {
	return glGetUniformLocation(m_RendererId, name.c_str());
}

void Shader::setInt(const std::string& name, const GLint& value) const {
	GLCall(glUniform1i(glGetUniformLocation(m_RendererId, name.c_str()), value));
}

void Shader::setFloat3(const std::string& name, const float& x, const float& y, const float& z) const {
	GLCall(glUniform3f(glGetUniformLocation(m_RendererId, name.c_str()), x, y, z));
}

void Shader::setFloat3(const GLuint& location, const float& x, const float& y, const float& z) const {
	GLCall(glUniform3f(location, x, y, z));
}

void Shader::setFloat4(const std::string& name, const float& x, const float& y, const float& z, const float& w) const {
	GLCall(glUniform4f(glGetUniformLocation(m_RendererId, name.c_str()), x, y, z, w));
}

void Shader::setVec4(const std::string& name, const glm::vec4& vector) const {
	GLCall(glUniform4fv(glGetUniformLocation(m_RendererId, name.c_str()), 1, &vector[0]));
}

void Shader::setVec4(const GLuint& index, const glm::vec4& vector) const {
	GLCall(glUniform4fv(index, 1, &vector[0]));
}

void Shader::setMat4(const GLuint& index, const glm::mat4& matrix) const {
	GLCall(glUniformMatrix4fv(index, 1, GL_FALSE, &matrix[0][0]));
}

void Shader::setMat4(const std::string& name, const glm::mat4& matrix) const {
	GLCall(glUniformMatrix4fv(glGetUniformLocation(m_RendererId, name.c_str()), 1, GL_FALSE, &matrix[0][0]));
}
