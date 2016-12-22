#pragma once

#include "../game/Entity.h"
#include "../graphics/Camera.h"

#include "../glm/glm.hpp"

namespace game
{
	class Level;
}


namespace game
{
	class Player : public game::Entity
	{
		Level& level;

		graphics::Camera camera;

		glm::vec3 position;
		glm::vec3 orientation;
		glm::vec3 rotation;

		float speed;
		float acceleration;

		// Used to limit player movement
		double max_yaw;
		double max_roll;

	public:
		Player(Level& level);
		~Player();

		virtual void update(float dt);

		glm::vec3 get_position();
		GLfloat getX();
		GLfloat getY();
		GLfloat getZ();

		graphics::Camera& get_camera();

		void set_position(glm::vec3 position);
		void set_position(GLfloat x, GLfloat y, GLfloat z);
		void move(glm::vec3 offset);
		void set_rotation(glm::vec3 rotation);
		void set_rotation(GLfloat x, GLfloat y, GLfloat z);
		void rotate(glm::vec3 offset);
	};
}


