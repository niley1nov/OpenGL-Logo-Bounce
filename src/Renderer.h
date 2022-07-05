#pragma once
#ifndef RENDER_H
#define RENDER_H

#include<GLEW/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/ext/matrix_transform.hpp>
#include<glm/gtx/color_space.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/random.hpp>
#include<algorithm>
#include<iterator>
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
#include<random>
#include<map>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError(); \
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void APIENTRY glDebugOutput(GLenum source,
	GLenum,
	GLuint,
	GLenum,
	GLsizei,
	const GLchar*,
	const void*);
GLenum glCheckError_(const char*, int);

std::string convert(int a);
void GLClearError();
bool GLLogCall(const char* function, const char* file, int LineNo);
void key_callback(GLFWwindow*, int, int, int, int);
int initGLFW();
void setupDebug();

class Renderer {

};

#endif