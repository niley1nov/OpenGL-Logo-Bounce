#pragma once

#include"Renderer.h"
#include"VertexArray.h"
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include"IndexBuffer.h"
#include"Shader.h"
#include"Texture.h"

class Logo {
private:
	GLfloat width, height;
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;
	Texture texture;
	Shader shader;
	glm::vec2 position;
	glm::vec2 velocity;
	glm::mat4 model;
	glm::vec4 color;
	GLuint hue;
	GLfloat time;
	GLfloat oldTime;
	GLboolean changeColor;

	GLfloat getDeltaTime();
	GLboolean getCollisionX(const GLfloat&);
	GLboolean getCollisionY(const GLfloat&);
	
public:
	Logo();
	~Logo();
	void update(const glm::vec3&);
	const Shader& getShader();
	GLuint getIndicesCount();
};