#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;

uniform mat4 model;
uniform vec3 color;

out vec4 vertexColor;

void main() {
	gl_Position = model * vec4(aPos, 1.0);
	vertexColor = vec4(aColor * color, 1.0);
}