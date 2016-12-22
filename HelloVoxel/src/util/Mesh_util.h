#pragma once

#include "../glad/glad.h"


namespace graphics
{
	class Mesh;
	struct Texture;
}


namespace util
{
	graphics::Texture gen_one_color_tex(
		GLuint w, GLuint h, GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	graphics::Texture gen_black_cross_tex(
		GLuint w, GLuint h, GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	graphics::Mesh gen_textured_cube(graphics::Texture texture);
}