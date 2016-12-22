#include "Camera.h"


graphics::Camera::Camera(glm::vec3 position, glm::vec3 direction, float FOV)
	: position(position), front(direction), FOV(glm::radians(FOV))
{
	right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), front));
	up = glm::cross(front, right);
}

graphics::Camera::~Camera()
{
}

GLfloat graphics::Camera::get_FOV() const
{
	return FOV;
}

glm::vec3 graphics::Camera::get_position() const
{
	return position;
}

glm::vec3 graphics::Camera::get_rotation() const
{
	return rotation;
}

glm::vec3 graphics::Camera::get_front_vector() const
{
	return front;
}

glm::vec3 graphics::Camera::get_up_vector() const
{
	return up;
}

glm::vec3 graphics::Camera::get_right_vector() const
{
	return right;
}

void graphics::Camera::set_position(glm::vec3 position)
{
	this->position = position;
}

void graphics::Camera::set_position(GLfloat x, GLfloat y, GLfloat z)
{
	this->position = { x, y, z };
}

void graphics::Camera::set_rotation(glm::vec3 rotation)
{
	set_rotation(rotation.x, rotation.y, rotation.z);
}

void graphics::Camera::set_rotation(GLfloat x, GLfloat y, GLfloat z)
{
	this->rotation = { x, y, z };
	front = glm::vec3(cos(x) * sin(y), sin(x), cos(x) * cos(y));
	right = glm::vec3(sin(y - M_PI / 2), 0.0f, cos(y - M_PI / 2));
	up = glm::vec3(sin(z), cos(z), 0.0f);
}

void graphics::Camera::set_direction(glm::vec3 direction)
{
	this->front = direction;
	right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), front));
	up = glm::cross(front, right);
}


