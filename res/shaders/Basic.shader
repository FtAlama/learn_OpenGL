#shader	vertex
#version 330 core

layout (location = 0) in vec4 position;

void main()
{
	gl_Position = vec4(position.x + 0.1f, position.y + 0.1f, position.z + 0.1f, position.w);
}

#shader fragment
#version 330 core

uniform vec4 u_color;

layout (location = 0) out vec4 color;

void main()
{
	color = u_color;
}
