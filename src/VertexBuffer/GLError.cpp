#include "Application.hpp"
#include <iostream>

void	GLClearError(void)
{
	while (glGetError() != GL_NO_ERROR) ;
}

bool	GLLogCall(const char *function, const char *file, int line)
{
	GLenum	error;

	if ((error = glGetError()))
	{
		std::cout << "GL error: " << error << "\nfunction: "
			<< function  << "\nfile : " << file << "\nline: " << line << std::endl;
		return (false);
	}
	return (true);
}
