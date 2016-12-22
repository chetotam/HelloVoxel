#include "Voxel.h"


game::Voxel::Voxel(graphics::Mesh& mesh) : mesh(mesh)
{
}

game::Voxel::~Voxel()
{
}

void game::Voxel::update(float dt)
{
	position += speed * dt;
	speed += acceleration * dt;
}

glm::vec3 game::Voxel::get_position() const
{
	return position;
}

glm::vec3 game::Voxel::get_rotation() const
{
	return rotation;
}

glm::vec3 game::Voxel::get_scale() const
{
	return scale;
}

graphics::Mesh& game::Voxel::get_mesh()
{
	return mesh;
}

void game::Voxel::set_position(glm::vec3 position)
{
	this->position = position;
}

void game::Voxel::set_rotation(glm::vec3 rotation)
{
	this->rotation = rotation;
}

void game::Voxel::set_scale(glm::vec3 scale)
{
	this->scale = scale;
}

void game::Voxel::set_speed(glm::vec3 scale)
{
	this->speed = speed;
}

void game::Voxel::set_acceleration(glm::vec3 scale)
{
	this->acceleration = acceleration;
}
