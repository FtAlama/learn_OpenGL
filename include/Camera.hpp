#ifndef CAMERA_H
#	define CAMERA_H

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

enum Camera_movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  4.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera
{
	public:
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 world_up;
		float			yaw;
		float			pitch;
		float			movement_speed;
		float			mouse_sensitivity;
		float			zoom;

		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
				 glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
		Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch);
		glm::mat4	getViewMatrix();
		void			processKeyboard(Camera_movement direction, float delta_time);
		void			processMouseMouvement(float x_offset, float y_offset, GLboolean constrainPitch);
		void			processMouseScroll(float y_offset);
	
	private:
		void			updateCameraVectors();

};

#endif
