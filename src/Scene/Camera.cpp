#include "Application.hpp"
#include "geometric.hpp"

Camera::Camera(point position, point target) : pos(position), target(target)
{
	this->setNewDirection(); 
	this->setNewRightAxis();
	this->setNewUpAxis();
}

void	Camera::setNewDirection()
{ this->direction = glm::normalize(this->target - this->pos); }

void	Camera::setNewRightAxis()
{
	glm::vec3 u(0.0f, 1.0f, 0.0f);
	this->right_axis = glm::normalize(glm::cross(u, this->direction));
}

void	Camera::setNewUpAxis()
{
	this->up_axis = glm::cross(this->direction, this->right_axis);
}
