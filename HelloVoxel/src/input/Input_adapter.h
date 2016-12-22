#pragma once

#include "Window_listener.h"
#include "Mouse_listener.h"
#include "Keyboard_listener.h"

namespace input
{
	class Input_adapter :
		public input::Window_listener,
		public input::Mouse_listener,
		public input::Keyboard_listener
	{
	public:
		Input_adapter();
		virtual ~Input_adapter();

		// Inherited via Window_listener
		virtual void on_window_iconify(display::Window& window) override;
		virtual void on_window_restore(display::Window& window) override;
		virtual void on_window_focus(display::Window& window) override;
		virtual void on_window_defocus(display::Window& window) override;
		virtual void on_window_move(display::Window& window, int x, int y) override;
		virtual void on_window_resize(display::Window& window, int width, int height) override;
		virtual void on_window_close(display::Window& window) override;

		// Inherited via Mouse_listener
		virtual void on_mouse_enter(display::Window& window) override;
		virtual void on_mouse_leave(display::Window& window) override;
		virtual void on_mouse_move(display::Window& window, double x, double y) override;
		virtual void on_mouse_click(
			display::Window& window, int button, int action, int mods) override;
		virtual void on_mouse_scroll(
			display::Window& window, double x_offset, double y_offset) override;

		// Inherited via Keyboard_listener
		virtual void on_key_press(
			display::Window& window, int key, int scancode, int action, int mods) override;
	};
}
