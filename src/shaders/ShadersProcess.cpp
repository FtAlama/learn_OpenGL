#include "Application.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

std::string	Shader::ParseShaderFile(const char *filepath)
{
	std::string		shader_code;
	std::ifstream	shader_file;

	shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		shader_file.open(filepath);
		std::stringstream shader_stream;
		shader_stream << shader_file.rdbuf();
		shader_file.close();
		shader_code = shader_stream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Error: file shader not succesfully read\n";
	}
	return (shader_code);
}

unsigned int	Shader::CompileShader(const char **shader_code, unsigned int type)
{
	unsigned int	shader;
	int						success;

	shader = glCreateShader(type);
	glShaderSource(shader, 1, shader_code, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int	length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char *message = (char *) alloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);
		std::cout << "Failed to compiled : "
				<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shader);
		return (0);
	}
	return (shader);
}
