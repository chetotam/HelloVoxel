#include "Mesh.h"


graphics::Mesh::Mesh()
{
}

graphics::Mesh::Mesh(
	const std::vector<Vertex>& vertices,
	const std::vector<GLuint>& indices,
	const Texture& texture)
	: vertices(vertices), indices(indices), texture(texture)
{
	// Create and bind VAO
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	// Create and bind VBO
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		this->vertices.size() * sizeof(Vertex),
		&this->vertices[0],
		GL_STATIC_DRAW);

	// Set vertex attribure pointers (0 - colors, 1 - normals, 2 - uv)
	glVertexAttribPointer(
		0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glVertexAttribPointer(
		1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glVertexAttribPointer(
		2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texture_coords));

	// Create and bind EBO
	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		this->indices.size() * sizeof(GLuint),
		&this->indices[0],
		GL_STATIC_DRAW);
	
	// Unbind VAO
	glBindVertexArray(0);

	// Create and bind texture
	glGenTextures(1, &this->texture.name);
	glBindTexture(GL_TEXTURE_2D, this->texture.name);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		this->texture.width,
		this->texture.height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		this->texture.data.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

graphics::Mesh::~Mesh()
{
	// TODO: check if I need some cleanup here
}

void graphics::Mesh::bind()
{
	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

void graphics::Mesh::unbind()
{
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

int graphics::Mesh::get_vertex_count() const
{
	return this->indices.size();
}

GLuint graphics::Mesh::get_texture() const
{
	return this->texture.name;
}

