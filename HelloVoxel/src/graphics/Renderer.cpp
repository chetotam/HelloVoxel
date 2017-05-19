#include "Renderer.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtx/euler_angles.hpp"

#include "../graphics/Program.h"
#include "../graphics/Camera.h"
#include "../graphics/Mesh.h"
#include "../game/Voxel.h"
#include "../display/Window.h"


graphics::Renderer::Renderer() :
	program(graphics::Program("./res/shaders/vert.glsl", "./res/shaders/frag.glsl"))
{
	// TODO: This should be called right after context (GLFW_window) created
	//gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// TODO: Check if I need this
	//glEnable(GL_TEXTURE_2D);

	// TODO: Check why this not working (mb fix cube normals?)
	//glEnable(GL_CULL_FACE);

	// TODO: Enable this when scene sorting implemented
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// TODO: Looks like this should be done somewhere else (Program itself?)
	program.add_uniform("model");
	program.add_uniform("view");
	program.add_uniform("projection");
	program.add_uniform("view_Position");
	program.add_uniform("dir_Light.direction");
	program.add_uniform("dir_Light.ambient");
	program.add_uniform("dir_Light.diffuse");
	program.add_uniform("dir_Light.specular");
	program.add_uniform("fog.color");
	program.add_uniform("fog.density");
}

graphics::Renderer::~Renderer()
{
}

void graphics::Renderer::render(
	const display::Window & window, std::vector<game::Voxel>& voxels, Camera & camera)
{
	aspect_ratio = (float)window.get_width() / (float)window.get_height();
	glViewport(0, 0, window.get_width(), window.get_height());

	program.bind();

	for (game::Voxel v : voxels) {
		// Create transformation matrices for each voxel and pass them as uniforms
		// Model matrix
		glm::mat4 model;
		model = glm::translate(model, v.get_position());
		model = model * glm::orientate4(v.get_rotation());
		model = glm::scale(model, v.get_scale());
		program.set_uniform("model", model);
		// View matrix
		glm::mat4 view = glm::lookAt(
			camera.get_position(),
			camera.get_position() + camera.get_front_vector(),
			camera.get_up_vector());
		program.set_uniform("view", view);
		// Projection matrix
		glm::mat4 projection = glm::perspective(camera.get_FOV(), aspect_ratio, z_near, z_far);
		program.set_uniform("projection", projection);

		program.set_uniform("view_Position", camera.get_position());

		// TODO: Fix this all. Maybe use Scene class
		program.set_uniform("dir_Light.direction", glm::normalize(glm::vec3(-0.1f, -0.5f, 0.4f)));
		program.set_uniform("dir_Light.ambient", { 0.4f, 0.4f, 0.4f });
		program.set_uniform("dir_Light.diffuse", { 0.9f, 0.9f, 0.9f });
		program.set_uniform("dir_Light.specular", { 0.0f, 0.0f, 0.0f });
		program.set_uniform("fog.color", { 0.9f, 0.9f, 0.9f });
		program.set_uniform("fog.density", 0.003f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, v.get_mesh().get_texture());

		// TODO: Maybe should not call this on every frame
		float anisotropy = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropy);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);

		v.get_mesh().bind();
		glDrawElements(GL_TRIANGLES, v.get_mesh().get_vertex_count(), GL_UNSIGNED_INT, 0);
		v.get_mesh().unbind();
	}

	program.unbind();
}


