#include "Application.hpp"
#include <iostream>

static void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	int fbWidth, fbHeight;
	(void) window; (void) width; (void) height;
	glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
	printf("Framebuffer size: %d x %d\n", fbWidth, fbHeight);
	glViewport(0, 0, fbWidth, fbHeight);
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
	window = glfwCreateWindow(500, 500, "learn OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return (NULL);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
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
	
	window = GLinit();
	if (window == nullptr)
		return (-1);
	vertex_draw vd = GLTwoTriangle();

	Shader prog1("res/shaders/uniform_vertex.shader", "res/shaders/Basic_fragment.shader");
	Shader prog2("res/shaders/Basic_vertex.shader", "res/shaders/Colored_fragment.shader");
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float x_axes = 0;
	bool	ret = false;
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		prog1.activate();
		prog1.setFloat("x", x_axes);
		glBindVertexArray(vd.vao[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		prog2.activate();
		glBindVertexArray(vd.vao[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		if (!ret)
		{
			x_axes += 0.001f;
			if (x_axes > 0.5f)
				ret = true;
		}
		else
		{
			x_axes -= 0.01f;
			if (x_axes < 0.0f)
				ret = false;
		}
	}
	glDeleteVertexArrays(2, vd.vao);
	glDeleteVertexArrays(2, vd.vbo);
	glDeleteProgram(prog1.id);
	glDeleteProgram(prog2.id);
	glfwTerminate();
	return (0);
}
