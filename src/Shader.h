#pragma once
#ifndef SHADER_S
#define SHADER_S

#include"Renderer.h"
#include<map>

class Shader {
private:
	GLuint m_RendererId;
	std::map<GLenum, std::string> shaderNames;
	std::map<GLenum, GLuint> shaderIds;

	void gl_checkCompileErrors(GLuint, const std::string&);

public:
	Shader();
	void copyShader(GLuint);
	void push(GLenum, const std::string&);
	void buildShader();
	GLuint getId();
	void use();
	GLuint getUniformLoc(const std::string&) const;
	void setInt(const std::string&, const GLint&) const;
	void setFloat3(const std::string&, const float&, const float&, const float&) const;
	void setFloat3(const GLuint&, const float&, const float&, const float&) const;
	void setFloat4(const std::string&, const float&, const float&, const float&, const float&) const;
	void setVec4(const std::string&, const glm::vec4&) const;
	void setVec4(const GLuint&, const glm::vec4&) const;
	void setMat4(const GLuint&, const glm::mat4&) const;
	void setMat4(const std::string&, const glm::mat4&) const;
};

#endif