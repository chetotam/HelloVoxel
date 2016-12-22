#include "Input_manager.h"

#include "../game/Game.h"

#include <GLFW\glfw3.h>

#include <iostream>
#include <algorithm>


input::Input_manager::Input_manager(game::Game& game) : game(game)
{
	this->game.get_window().add_window_listener(this);
	this->game.get_window().add_mouse_listener(this);
	this->game.get_window().add_keyboard_listener(this);
}

input::Input_manager::~Input_manager()
{
	// TODO: unregister listeners (important!)
}

double input::Input_manager::get_x_axis() const
{
	// Do I need member for this?
	float mouse_range = (this->game.get_window().get_width() / 2) / mouse_sensitivity;
	return x_axis / mouse_range;
}

double input::Input_manager::get_y_axis() const
{
	float mouse_range = (this->game.get_window().get_width() / 2) / mouse_sensitivity;
	return y_axis / mouse_range;
}

void input::Input_manager::on_window_close(display::Window& window)
{
	window.close();
}

void input::Input_manager::on_mouse_move(display::Window& window, double x, double y)
{
	float offset_x = x - mouse_x;
	float offset_y = y - mouse_y;
	mouse_x = x;
	mouse_y = y;

	float mouse_range = (this->game.get_window().get_width() / 2) / mouse_sensitivity;
	x_axis = std::max(std::min(mouse_range, x_axis + offset_x), -mouse_range); // std::clamp?
	y_axis = std::max(std::min(mouse_range, y_axis + offset_y), -mouse_range);
}

void input::Input_manager::on_mouse_enter(display::Window& window)
{
	// TODO: mb make Window class method for this
	//glfwSetInputMode(window.get_handle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void input::Input_manager::on_mouse_leave(display::Window& window)
{
	// TODO: mb make Window method for this
	//glfwSetInputMode(window.get_handle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
