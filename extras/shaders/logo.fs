#version 460 core

in vec2 outTexCord;

out vec4 color;

layout (location = 0) uniform vec4 outColor;
uniform sampler2D outTexture1;

void main() {
    color = texture(outTexture1, outTexCord) * outColor;
}