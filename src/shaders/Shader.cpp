#include "Application.hpp"
#include "gtc/type_ptr.hpp"
#include <iostream>
#include <string>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
	std::string		v_shader_code;
	std::string		f_shader_code;
	unsigned int	vertex;
	unsigned int	fragment;
	int						success;
	const char		*v_code;
	const char		*f_code;

	v_shader_code = this->ParseShaderFile(vertexPath);
	f_shader_code = this->ParseShaderFile(fragmentPath);
	v_code = v_shader_code.c_str();
	f_code = f_shader_code.c_str();
	vertex = this->CompileShader(&v_code, GL_VERTEX_SHADER);
	fragment = this->CompileShader(&f_code, GL_FRAGMENT_SHADER);
	this->id = glCreateProgram();	
	glAttachShader(this->id, vertex);
	glAttachShader(this->id, fragment);
	glLinkProgram(this->id);
	glValidateProgram(this->id);
	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if(!success)
		std::cout << "ERROR: SHADER_PROGRAM::LINKING_FAILED\n"; 
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void	Shader::activate()
{
	glUseProgram(this->id);
}
void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(this->id, name.c_str()), value); 
}
void	Shader::setMat4(const std::string &name, glm::mat4 value) const
{
	unsigned int transformLoc = glGetUniformLocation(this->id, name.c_str());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(value));
}
