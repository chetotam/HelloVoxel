#pragma once

#include "Entity.h"
#include "../glm/glm.hpp"

namespace graphics
{
	class Mesh;
	class Program;
}


namespace game
{
	class Voxel : public Entity
	{
		graphics::Mesh& mesh;
		//graphics::Program& program; TODO: Decide where to place shader program
		// now only instance from Renderer class used for everything

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec3 speed;
		glm::vec3 acceleration;

	public:
		Voxel(graphics::Mesh& mesh);
		virtual ~Voxel();

		virtual void update(float dt);

		graphics::Mesh& get_mesh();

		glm::vec3 get_position() const;
		glm::vec3 get_rotation() const;
		glm::vec3 get_scale() const;
		
		void set_position(glm::vec3 position);
		void set_rotation(glm::vec3 rotation);
		void set_scale(glm::vec3 scale);
		void set_speed(glm::vec3 scale);
		void set_acceleration(glm::vec3 scale);
	};
}


