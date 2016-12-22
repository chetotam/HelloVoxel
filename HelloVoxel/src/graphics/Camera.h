#pragma once

#define _USE_MATH_DEFINES

#include "../glm/glm.hpp"
#include "../glad/glad.h"

#include <cmath>


namespace graphics
{
	class Camera
	{
		glm::vec3 position;
		glm::vec3 rotation; // Yaw, pitch, roll
		// TODO: use quaternion for rotation

		GLfloat FOV;

		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;

	public:
		Camera(glm::vec3 position, glm::vec3 rotation, float FOV);
		~Camera();

		GLfloat get_FOV() const;
		glm::vec3 get_position() const;
		glm::vec3 get_rotation() const;
		glm::vec3 get_front_vector() const;
		glm::vec3 get_up_vector() const;
		glm::vec3 get_right_vector() const;

		void set_position(glm::vec3 position);
		void set_position(GLfloat x, GLfloat y, GLfloat z);
		void set_rotation(glm::vec3 rotation);
		void set_rotation(GLfloat x, GLfloat y, GLfloat z);
		void set_direction(glm::vec3 direction); // set front vector
	};
}