#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColor; 

out vec3	ourColor;

uniform float x;

void main()
{
	gl_Position = vec4(position.x + x, position.y, position.z, 1);
	ourColor = aColor;
}
