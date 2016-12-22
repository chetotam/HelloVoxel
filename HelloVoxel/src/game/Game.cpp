#include "Game.h"

#include "GLFW\glfw3.h"
#include <iostream>


game::Game::Game() : window(1280, 720, "HelloVoxel"), level(*this), input(*this)
{
}

game::Game::~Game()
{
	window.close();
}

void game::Game::start()
{
	running = true;

	double previous_time = glfwGetTime();
	double current_time;
	float delta = 0.0f;

	while (running) {
		if (!paused) {
			current_time = glfwGetTime();
			delta = current_time - previous_time;
			previous_time = current_time;

			update(delta);
			render();
		}
	}
}

void game::Game::stop()
{
	running = false;
}

void game::Game::pause()
{
	paused = true;
}

void game::Game::resume()
{
	paused = false;
}

display::GLFW_window & game::Game::get_window()
{
	return window;
}

graphics::Renderer& game::Game::get_renderer()
{
	return renderer;
}

input::Input_manager& game::Game::get_input()
{
	return input;
}

void game::Game::update(float dt)
{
	glfwPollEvents();
	level.update(dt);
}

void game::Game::render()
{
	// TODO: Move this to Renderer when it will be ready
	glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer.render(window, level.get_tiles(), level.get_player().get_camera());
	renderer.render(window, level.get_voxels(), level.get_player().get_camera());
	renderer.render(window, level.get_powerups(), level.get_player().get_camera());
	
	// TODO: Move this to Renderer
	glfwSwapBuffers(window.get_handle());
}
