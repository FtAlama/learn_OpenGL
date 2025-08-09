#include "Application.hpp"
#include <iostream>
#include <string>

static void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

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
	std::string vertex_source;
	std::string fragment_source;
	
	std::string vertex("res/shaders/Basic_vertex.shader");
	std::string fragment("res/shaders/Basic_fragment.shader");
	std::string yellow_fragment("res/shaders/Yellow_fragment.shader");

	window = GLinit();
	if (window == nullptr)
		return (-1);
	vertex_draw vd = GLTwoTriangle();

	vertex_source = ParseShader(vertex);
	fragment_source = ParseShader(fragment);
	unsigned int shader = glCreateProgram();
	CreateAndAttachShaders(vertex_source, GL_VERTEX_SHADER, shader);
	CreateAndAttachShaders(fragment_source, GL_FRAGMENT_SHADER, shader);

	unsigned int shader2 = glCreateProgram();
	fragment_source = ParseShader(yellow_fragment);
	CreateAndAttachShaders(vertex_source, GL_VERTEX_SHADER, shader2);
	CreateAndAttachShaders(fragment_source, GL_FRAGMENT_SHADER, shader2);
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//GLCHECKCALLLoop(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		GLCHECKCALLLoop(glUseProgram(shader));
		int location = glGetUniformLocation(shader, "u_color");
		glUniform4f(location, 0.2f, 0.5f, 0.2f, 1.0f);
		glBindVertexArray(vd.vao[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		GLCHECKCALLLoop(glUseProgram(shader2));
		glBindVertexArray(vd.vao[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(2, vd.vao);
	glDeleteVertexArrays(2, vd.vbo);
	glDeleteProgram(shader);
	glDeleteProgram(shader2);
	glfwTerminate();
	return (0);
}
