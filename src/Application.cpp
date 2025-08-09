#include "Application.hpp"
#include <iostream>

static GLFWwindow* GLinit()
{
	GLFWwindow* window;

  if (!glfwInit())
		return (NULL);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	window = glfwCreateWindow(500, 500, "simple blue triangle", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return (NULL);
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return (NULL);
	}
	return (window);
}

int main(void)
{
	GLFWwindow*	window;
	std::string filepath("res/shaders/Basic.shader");

	window = GLinit();
	if (window == nullptr)
		return (-1);
	GLElementVertexRectangle();
	ShaderProgramSource sh = ParseShader(filepath);
	unsigned int shader = CreateShaders(sh.vertex_source, sh.fragment_source);
	GLCHECKCALL(glUseProgram(shader));

	int location = glGetUniformLocation(shader, "u_color");
	glUseProgram(shader);
	glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);

	float	r = 0.0f;
	float	incr = 0.05f;
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUniform4f(location, r, 0.3f, 0.8f, 1.0f);
		GLCHECKCALLLoop(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		
		if (r > 1.0f)
			incr = -0.05f;
		else if (r < 0.0f)
			incr = 0.05f;
		r += incr;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shader);
	glfwTerminate();
	return (0);
}
