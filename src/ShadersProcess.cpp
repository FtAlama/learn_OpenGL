#include "Application.hpp"
#include <fstream>
#include <iostream>
#include <string>

std::string	ParseShader(std::string& filepath)
{
	std::string	ss;
	std::string line;
	std::ifstream stream(filepath);

	while (getline(stream, line))
		ss += line += "\n";
	return (ss);
}

unsigned int	CompileShader(const std::string& source, unsigned int type)
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
		std::cout << "Failed to compiled : "
				<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return (0);
	}
	return (id);
}

void	CreateAndAttachShaders(const std::string& shader, unsigned int type, unsigned int &prog)
{
	unsigned int sh = CompileShader(shader, type);

	glAttachShader(prog, sh);
	glLinkProgram(prog);
	glValidateProgram(prog);
	glDeleteShader(sh);
}
