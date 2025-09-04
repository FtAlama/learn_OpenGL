#ifndef APPLICATION_HPP
# define APPLICATION_HPP

#include "fwd.hpp"
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <string>
# include <glm.hpp>
# include <gtc/matrix_transform.hpp>
# include <gtc/type_ptr.hpp>

// GL error			----> DEPRECATED : NEED TO REDO
# define	ASSERT(x) if (!(x)) break;
void			GLClearError(void);
bool			GLLogCall(const char *function, const char *file, int line);
# define	GLCHECKCALLLoop(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
# define	GLCHECKCALL(x) GLClearError(); x; GLLogCall(#x, __FILE__, __LINE__)


# define WITDH	800
# define HEIGHT	600

typedef glm::vec3 point;

typedef glm::vec3 vector;

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
		void					setMat4(const std::string &name, glm::mat4 value) const;
	private:
		std::string		ParseShaderFile(const char *filepath);
		unsigned int	CompileShader(const char **shader_code, unsigned int type);

};

class Texture
{
	public:
		unsigned int id;
		Texture(const char *tex_path, unsigned int type);
		bool	Error();
	private:
		int									witdh;
		int									height;
		int									nrChannels;
		unsigned char				*data;
};


// Vertex
struct vertex_draw
{
	unsigned int vao[2];
	unsigned int vbo[2];
};

vertex_draw			GLTwoTriangle();
vertex_draw			GLElementVertexTexture();


#endif
