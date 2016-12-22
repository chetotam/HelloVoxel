#pragma once

#include "../glad/glad.h"
#include "../glm/glm.hpp"

#include <vector>


namespace graphics
{
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texture_coords;
	};

	struct Texture {
		GLuint name;
		GLuint width;
		GLuint height;
		std::vector<GLubyte> data;
	};

	class Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		Texture texture;

		GLuint VAO;
		GLuint VBO; // mb dont need this as class member
		GLuint EBO; // mb dont need this as class member

	public:
		Mesh();
		Mesh(
			const std::vector<Vertex>& vertices,
			const std::vector<GLuint>& indices,
			const Texture& texture);
		~Mesh();

		void bind();
		void unbind();

		int get_vertex_count() const;
		GLuint get_texture() const;
	};
}


