#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

static unsigned int	CompileShader(const std::string& source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char *str = source.c_str();
	int		result = 0;

	glShaderSource(id, 1, &str, NULL);
	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int	length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char *) alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compiled : " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return (0);
	}
	return (id);
}

static unsigned int CreateShaders(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int prog = glCreateProgram();
	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);
	glValidateProgram(prog);

	glDeleteShader(vs);
	glDeleteShader(fs);
	return (prog);
}

int main(void)
{
	GLFWwindow* window;
	unsigned int	buff;
	float					positions[6] = {
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f
	};

  if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return (1);
	}
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &buff);
	glBindBuffer(GL_ARRAY_BUFFER, buff);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	std::string vertexShader = 
		"#version 330 core\n"
		"\n"
		"layout (location = 0) in vec4 position;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = position;\n"
		"}\n";

	std::string fragmentShader = 
		"#version 330 core\n"
		"\n"
		"layout (location = 0) out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

	unsigned int shader = CreateShaders(vertexShader, fragmentShader);
	glUseProgram(shader);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}
