#pragma once

#include "../glad/glad.h"
#include "../glm/glm.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>


namespace graphics
{
	class Program
	{
		GLuint name;
		GLuint vertex_shader;
		GLuint fragment_shader;
		std::map<std::string, GLuint> uniforms;

	public:
		Program();
		Program(std::string vertex_path, std::string fragment_path);
		~Program();

		void bind();
		void unbind();

		void add_uniform(std::string uniform_name);
		// TODO: implement some kind of shader parser to retrieve uniforms from file directly
		void set_uniform(std::string uniform_name, glm::mat4 matrix);
		void set_uniform(std::string uniform_name, glm::vec3 data);
		void set_uniform(std::string uniform_name, GLfloat data);

	private:
		GLuint compile_shader(const GLchar* src, GLenum type);
	};
}


