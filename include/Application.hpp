#ifndef APPLICATION_HPP
# define APPLICATION_HPP

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <string>

// GL error			----> DEPRECATED : NEED TO REDO
# define	ASSERT(x) if (!(x)) break;
void			GLClearError(void);
bool			GLLogCall(const char *function, const char *file, int line);
# define	GLCHECKCALLLoop(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
# define	GLCHECKCALL(x) GLClearError(); x; GLLogCall(#x, __FILE__, __LINE__)


// Shaders
class Shader
{
	public:
		unsigned int	id;
		Shader(const char *vertexPath, const char *fragmentPath);
		void					activate();
		void					setBool(const std::string &name, bool value) const;
		void					setInt(const std::string &name, int value) const;
		void					setFloat(const std::string &name, float value) const;
	private:
		std::string		ParseShaderFile(const char *filepath);
		unsigned int	CompileShader(const char **shader_code, unsigned int type);

};


// Vertex
struct vertex_draw
{
	unsigned int vao[2];
	unsigned int vbo[2];
};
void						GLElementVertexRectangle();
vertex_draw			GLTwoTriangle();

#endif
