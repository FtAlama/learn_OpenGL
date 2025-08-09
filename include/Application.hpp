#ifndef APPLICATION_HPP
# define APPLICATION_HPP

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <string>

// GL error
# define ASSERT(x) if (!(x)) break;
void	GLClearError(void);
bool	GLLogCall(const char *function, const char *file, int line);
# define GLCHECKCALLLoop(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
# define GLCHECKCALL(x) GLClearError(); x; GLLogCall(#x, __FILE__, __LINE__)

// Shaders
std::string		ParseShader(std::string& filepath);
unsigned int	CompileShader(const std::string& source, unsigned int type);
void				CreateAndAttachShaders(const std::string& shader, unsigned int type, unsigned int &prog);

struct vertex_draw
{
	unsigned int vao[2];
	unsigned int vbo[2];
};

// Vertex
void						GLElementVertexRectangle();
vertex_draw			GLTwoTriangle();

#endif
