#include "Mesh_util.h"

#include "../graphics/Mesh.h"

#include <vector>


// Generates simple RGBA texture with specified width, height and color
// btw shouldn't textures be square?
graphics::Texture util::gen_one_color_tex(
	GLuint w, GLuint h, GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	graphics::Texture texture;
	texture.width = w;
	texture.height = h;
	for (int i = 0; i < texture.height; ++i) {
		for (int j = 0; j < texture.width; ++j) {
			texture.data.push_back(r);
			texture.data.push_back(g);
			texture.data.push_back(b);
			texture.data.push_back(a);
		}
	}
	return texture;
}

// Generates RGBA texture with specified width, height and color and almost black assymetric cross
// for ground
graphics::Texture util::gen_black_cross_tex(
	GLuint w, GLuint h, GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	graphics::Texture texture;
	texture.width = w;
	texture.height = h;

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			// ok, this is weird
			if ((i >= h / 2 - 1 && i < h / 2 + 1 && j >= 3 * w / 8 && j < 5 * w / 8) ||
				(j >= w / 2 - 1 && j < w / 2 + 1 && i >= h / 4 && i < 3 * h / 4)) {
				texture.data.push_back(24);
				texture.data.push_back(24);
				texture.data.push_back(24);
				texture.data.push_back(24);
			}
			else {
				texture.data.push_back(r);
				texture.data.push_back(g);
				texture.data.push_back(b);
				texture.data.push_back(a);
			}
		}
	}
	return texture;
}

// Well, textured cube
// TODO: implement mesh and texture loading
graphics::Mesh util::gen_textured_cube(graphics::Texture texture)
{
	// 1x1 cube vertex coordinates, normals and uv
	std::vector<graphics::Vertex> vertices{
		{ { -0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f }, { 0.0f, 0.0f } },
		{ { 0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f } },
		{ { 0.5f,  0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f }, { 1.0f, 1.0f } },
		{ { 0.5f,  0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f }, { 1.0f, 1.0f } },
		{ { -0.5f,  0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f }, { 0.0f, 1.0f } },
		{ { -0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f }, { 0.0f, 0.0f } },

		{ { -0.5f, -0.5f,  0.5f }, { 0.0f,  0.0f, 1.0f }, { 0.0f, 0.0f } },
		{ { 0.5f, -0.5f,  0.5f }, { 0.0f,  0.0f, 1.0f }, { 1.0f, 0.0f } },
		{ { 0.5f,  0.5f,  0.5f }, { 0.0f,  0.0f, 1.0f }, { 1.0f, 1.0f } },
		{ { 0.5f,  0.5f,  0.5f }, { 0.0f,  0.0f, 1.0f }, { 1.0f, 1.0f } },
		{ { -0.5f,  0.5f,  0.5f }, { 0.0f,  0.0f, 1.0f }, { 0.0f, 1.0f } },
		{ { -0.5f, -0.5f,  0.5f }, { 0.0f,  0.0f, 1.0f }, { 0.0f, 0.0f } },

		{ { -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f } },
		{ { -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f } },
		{ { -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f } },
		{ { -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f } },
		{ { -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f } },
		{ { -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f } },

		{ { 0.5f,  0.5f,  0.5f }, { 1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f } },
		{ { 0.5f,  0.5f, -0.5f }, { 1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f } },
		{ { 0.5f, -0.5f, -0.5f }, { 1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f } },
		{ { 0.5f, -0.5f, -0.5f }, { 1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f } },
		{ { 0.5f, -0.5f,  0.5f }, { 1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f } },
		{ { 0.5f,  0.5f,  0.5f }, { 1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f } },

		{ { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f } },
		{ { 0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f } },
		{ { 0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f } },
		{ { 0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f } },
		{ { -0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f,  0.0f }, { 0.0f, 0.0f } },
		{ { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f } },

		{ { -0.5f,  0.5f, -0.5f }, { 0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f } },
		{ { 0.5f,  0.5f, -0.5f }, { 0.0f,  1.0f,  0.0f }, { 1.0f, 1.0f } },
		{ { 0.5f,  0.5f,  0.5f }, { 0.0f,  1.0f,  0.0f }, { 1.0f, 0.0f } },
		{ { 0.5f,  0.5f,  0.5f }, { 0.0f,  1.0f,  0.0f }, { 1.0f, 0.0f } },
		{ { -0.5f,  0.5f,  0.5f }, { 0.0f,  1.0f,  0.0f }, { 0.0f, 0.0f } },
		{ { -0.5f,  0.5f, -0.5f }, { 0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f } }
	};

	// cube indices
	std::vector<GLuint> indices{
		0, 1, 2, 3, 4, 5,
		6, 7, 8, 9, 10, 11,
		12, 13, 14, 15, 16, 17,
		18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29,
		30, 31, 32, 33, 34, 35 };

	return graphics::Mesh(vertices, indices, texture);
}
