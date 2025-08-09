#include "Application.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

ShaderProgramSource ParseShader(std::string& filepath)
{
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;
	std::stringstream ss[2];
	std::string line;
	std::ifstream stream(filepath);

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if(line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else if (type != ShaderType::NONE)
			ss[(int)type] << line << "\n";
	}
	return { ss[0].str(), ss[1].str() };
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

unsigned int CreateShaders(const std::string& vertexShader, const std::string& fragmentShader)
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
