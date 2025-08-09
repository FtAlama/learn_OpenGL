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

// GL error
# define ASSERT(x) if (!(x)) break;
void	GLClearError(void);
bool	GLLogCall(const char *function, const char *file, int line);
# define GLCHECKCALLLoop(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
# define GLCHECKCALL(x) GLClearError(); x; GLLogCall(#x, __FILE__, __LINE__)

// Shaders
ShaderProgramSource ParseShader(std::string& filepath);
unsigned int	CompileShader(const std::string& source, unsigned int type);
unsigned int CreateShaders(const std::string& vertexShader, const std::string& fragmentShader);

// Vertex
void	GLElementVertexRectangle();

#endif
