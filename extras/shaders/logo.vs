#version 460 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCord;

out vec2 outTexCord;

uniform	mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(position, 0.0f, 1.0f);
	outTexCord = texCord;
}