#include "Program.h"

#include "../util/File_util.h"

#include "../glm/gtc/type_ptr.hpp"


graphics::Program::Program()
{
}

graphics::Program::Program(std::string vertex_path, std::string fragment_path)
{
	// Compile shaders
	vertex_shader = compile_shader(
		util::file_to_string(vertex_path).c_str(), GL_VERTEX_SHADER);
	fragment_shader = compile_shader(
		util::file_to_string(fragment_path).c_str(), GL_FRAGMENT_SHADER);

	// Create and link program
	name = glCreateProgram();
	glAttachShader(name, vertex_shader);
	glAttachShader(name, fragment_shader);
	glLinkProgram(name);

	// Check for linking errors
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(name, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(name, 512, NULL, infoLog);
		std::cout << "Could not link program\n" << infoLog << "\n";
		// Or maybe throw exception?
	}
	// We no longer need this shaders
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}


graphics::Program::~Program()
{
	// Unbind and delete program
	unbind();
	if (name != NULL) {
		if (vertex_shader != NULL) {
			glDetachShader(name, vertex_shader);
		}
		if (fragment_shader != NULL) {
			glDetachShader(name, fragment_shader);
		}
		glDeleteProgram(name);
	}
}

void graphics::Program::bind()
{
	glUseProgram(name);
}

void graphics::Program::unbind()
{
	glUseProgram(0);
}

void graphics::Program::add_uniform(std::string uniform_name)
{
	GLuint location = glGetUniformLocation(name, uniform_name.c_str());
	if (location < 0) { // location actually can't be < 0, it rather would be max uint
		// TODO: Handle situation when there is no specified shader in file
		std::cout << "Uniform " << uniform_name << " not found";
	}
	uniforms.insert(std::make_pair(uniform_name, location));
}

void graphics::Program::set_uniform(std::string uniform_name, glm::mat4 data)
{
	glUniformMatrix4fv(uniforms[uniform_name], 1, GL_FALSE, glm::value_ptr(data));
}

void graphics::Program::set_uniform(std::string uniform_name, glm::vec3 data)
{
	glUniform3f(uniforms[uniform_name], data.x, data.y, data.z);
}

void graphics::Program::set_uniform(std::string uniform_name, GLfloat data)
{
	glUniform1f(uniforms[uniform_name], data);
}

GLuint graphics::Program::compile_shader(const GLchar * src, GLenum type)
{
	// Create and compile shader
	GLuint name = glCreateShader(type);
	glShaderSource(name, 1, &src, NULL);
	glCompileShader(name);

	// Check for compilation errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(name, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(name, 512, NULL, infoLog);
		std::cerr << "Could not compile shader\n" << infoLog << "\n";
		// Or maybe throw exception?
	}
	return name;
}
