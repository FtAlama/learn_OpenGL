#ifndef APPLICATION_HPP
# define APPLICATION_HPP

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <string>

struct ShaderProgramSource
{
	std::string vertex_source;
	std::string fragment_source;
};

#endif
