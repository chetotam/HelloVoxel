#include "Player.h"

#include "../glm/gtx/rotate_vector.hpp"
#include "Game.h"
#include "Level.h"

#include <iostream>
#include <cmath>


game::Player::Player(Level& level) :
	level(level),
	camera(graphics::Camera(position, orientation, 60.0f)),
	speed(50.f),
	acceleration(1.0f),
	max_yaw(45.0f),
	max_roll(30.0f)
{
}


game::Player::~Player()
{
}

void game::Player::update(float dt)
{
	set_rotation(
		0.0f,
		glm::radians(-max_yaw * level.get_game().get_input().get_x_axis()),
		glm::radians(-max_roll * level.get_game().get_input().get_x_axis()));
	position += orientation * speed * dt;
	speed += acceleration * dt;

	camera.set_position(position);
	camera.set_rotation({glm::radians(6.0f), rotation.y / 3, rotation.z});
}

glm::vec3 game::Player::get_position()
{
	return position;
}

GLfloat game::Player::getX()
{
	return position.x;
}

GLfloat game::Player::getY()
{
	return position.y;
}

GLfloat game::Player::getZ()
{
	return position.z;
}

graphics::Camera& game::Player::get_camera()
{
	return camera;
}

void game::Player::set_position(glm::vec3 position)
{
	this->position = position;
	camera.set_position(this->position);
}

void game::Player::set_position(GLfloat x, GLfloat y, GLfloat z)
{
	set_position({ x, y, z });
}

void game::Player::move(glm::vec3 offset)
{
	this->position += offset;
}

void game::Player::set_rotation(glm::vec3 rotation)
{
	set_rotation(rotation.x, rotation.y, rotation.z);
}

void game::Player::set_rotation(GLfloat x, GLfloat y, GLfloat z)
{
	this->rotation = { x, y, z };
	orientation = glm::vec3(cos(x) * sin(y), sin(x), cos(x) * cos(y));
}

void game::Player::rotate(glm::vec3 offset)
{
	this->rotation += offset;
	orientation = glm::rotateY(orientation, offset.y);
}
