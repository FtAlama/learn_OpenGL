#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
			: front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM)
{
	this->position = position;
	this->world_up = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->updateCameraVectors();
}

Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch)
			: front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM)
{
	this->position = glm::vec3(pos_x, pos_y, pos_z);
	this->world_up = glm::vec3(up_x, up_y, up_z);
	this->yaw = yaw;
	this->pitch = pitch;
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  this->front = glm::normalize(front);
  this->right = glm::normalize(glm::cross(this->front, world_up)); 
  this->up = glm::normalize(glm::cross(right, this->front));
}

glm::mat4	Camera::getViewMatrix()
{
	return (glm::lookAt(this->position, this->position + this->front, this->up));
}

// void	Camera::processKeyboard(Camera_movement direction, float delta_time)
// {
// 	float	velocity = this->movement_speed * delta_time;
// 	if (direction == FORWARD)
//
// }
