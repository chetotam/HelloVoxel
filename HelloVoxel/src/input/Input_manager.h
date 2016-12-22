#pragma once

#include "Input_adapter.h"

namespace game
{
	class Game;
}


namespace input
{
	class Input_manager : public input::Input_adapter
	{
		game::Game& game;

		// cursor position values clamped to (-1; 1) range,
		// where 1 value means mouse travel equal to half of the window width when sensitivity = 1
		float x_axis;
		float y_axis;
		float mouse_sensitivity{ 1.0f };

		// actual mouse coordinates (could be quite big when GLFW_CURSOR_DISABLED is used)
		double mouse_x;
		double mouse_y;

		// TODO: Add support for mouse buttons / keyboard input

	public:
		Input_manager(game::Game& game);
		virtual ~Input_manager();

		double get_x_axis() const;
		double get_y_axis() const;

		virtual void on_window_close(display::Window& window) override;

		virtual void on_mouse_move(display::Window& window, double x, double y) override;
		virtual void on_mouse_enter(display::Window& window) override;
		virtual void on_mouse_leave(display::Window& window) override;
	};

}

