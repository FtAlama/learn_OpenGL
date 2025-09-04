#include "Application.hpp"
#include "Camera.hpp"
#include "GLFW/glfw3.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "fwd.hpp"
#include "geometric.hpp"
#include "trigonometric.hpp"
#include <iostream>

float	delta_time = 0.0f;
float	last_frame = 0.0f;

float	lastX = 0.0f;
float	lastY = 0.0f;

bool	firstMouse = true;

point	cameraPos = point(0.0f, 0.0f, 3.0f);
point	cameraFront = point(0.0f, 0.0f, -1.0f);
point cameraUp = point(0.0f, 1.0f, 0.0f);
float	yaw = -90.0f;
float	pitch = 0.0f;

float	fov = 60.0f;

static void	mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);
	float	x_offset;
	float	y_offset;
	float	sensitivity = 0.1f;

	if (firstMouse)
	{
		std::cout << "first step : " << xpos  << " " << ypos << std::endl;
		lastX = xpos;
		lastY = ypos;
	 	firstMouse = false;
		return ;
	}
	x_offset = xpos - lastX;
	y_offset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	x_offset *= sensitivity;
	y_offset *= sensitivity;
	
	yaw += x_offset;
	pitch += y_offset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;
	vector direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
	(void) window;
}

static void processInput(GLFWwindow *window, point *cameraPos, point *cameraFront, point *cameraUp)
{
	float	camera_sp = SPEED * delta_time;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		*cameraPos += camera_sp * *cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		*cameraPos -= camera_sp * *cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		*cameraPos -= glm::normalize(glm::cross(*cameraFront, *cameraUp)) * camera_sp;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		*cameraPos += glm::normalize(glm::cross(*cameraFront, *cameraUp)) * camera_sp;

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		*cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		*cameraFront = point(0.0f, 0.0f, -1.0f);
		firstMouse = true;
		yaw = -90.0f;
		pitch = 0.0f;
		fov = 60.0f;
	}
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	int fbWidth, fbHeight;
	(void) window; (void) width; (void) height;
	glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
	glViewport(0, 0, fbWidth, fbHeight);
}

static	void scroll_callback(GLFWwindow *window, double x_offset, double y_offset)
{
	fov -= (float) y_offset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 60.0f)
		fov = 60.0f;
	(void) window;
	(void) x_offset;
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
	window = glfwCreateWindow(WITDH, HEIGHT, "learn OpenGL", NULL, NULL);
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
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback); 
	return (window);
}

int main(void)
{
	GLFWwindow*	window;
	
	window = GLinit();
	if (window == nullptr)
		return (-1);
	Texture image_one("texture/house.jpg", GL_RGB);
	if (image_one.Error())
		return (-1);
	Texture image_two("texture/mojojo.png", GL_RGBA);
	if (image_two.Error())
		return (-1);

	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));	
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(fov), (float) WITDH / (float) HEIGHT, 0.1f, 100.f);

	//matrix tranformation for rectangle
	glm::mat4 trans = glm::mat4(1.0f);

	trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));

	vertex_draw vd = GLElementVertexTexture();

	Shader prog1("res/shaders/Tex_vertex.shader", "res/shaders/Tex_fragment.shader");
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
	};

	prog1.activate();
	prog1.setInt("texture1", 0);
	prog1.setInt("texture2", 1);
	prog1.setMat4("transform", trans);
	prog1.setMat4("model", model);
	prog1.setMat4("view", view);
	prog1.setMat4("projection", projection);
	float angle = 0;


	float current_frame; 
	while (!glfwWindowShouldClose(window))
	{
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;
		processInput(window, &cameraPos, &cameraFront, &cameraUp);

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, image_one.id);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, image_two.id);

		projection = glm::perspective(glm::radians(fov), (float) WITDH / (float) HEIGHT, 0.1f, 100.f);
		prog1.setMat4("projection", projection);

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		prog1.setMat4("view", view);

		prog1.activate();
		glBindVertexArray(vd.vao[0]);
		for (int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			angle = glm::radians(20.0f * i);
			if (angle <= 0)
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
			else	
				model = glm::rotate(model, (float)glfwGetTime() * angle, glm::vec3(0.5f, 1.0f, 0.0f));
			prog1.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(2, vd.vao);
	glDeleteVertexArrays(2, vd.vbo);
	glDeleteProgram(prog1.id);
	glfwTerminate();
	return (0);
}
