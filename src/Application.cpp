#include "Application.hpp"
#include "ext/matrix_transform.hpp"
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
	window = glfwCreateWindow(700, 500, "learn OpenGL", NULL, NULL);
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

	Texture image_one("texture/container.jpg", GL_RGB);
	if (image_one.Error())
		return (-1);
	Texture image_two("texture/awesomeface.png", GL_RGBA);
	if (image_two.Error())
		return (-1);

	glm::mat4 trans = glm::mat4(1.0f);

	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	vertex_draw vd = GLElementVertexTexture();

	Shader prog1("res/shaders/Tex_vertex.shader", "res/shaders/Tex_fragment.shader");
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	prog1.activate();
	prog1.setInt("texture1", 0);
	prog1.setInt("texture2", 1);
	prog1.setMat4("transform", trans);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, image_one.id);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, image_two.id);
	
		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		prog1.setMat4("transform", trans);
		
		prog1.activate();
		glBindVertexArray(vd.vao[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(2, vd.vao);
	glDeleteVertexArrays(2, vd.vbo);
	glDeleteProgram(prog1.id);
	glfwTerminate();
	return (0);
}
