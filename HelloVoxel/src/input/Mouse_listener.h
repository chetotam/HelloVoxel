#pragma once

namespace display
{
	class Window;
}


namespace input
{
	class Mouse_listener
	{
	public:
		virtual ~Mouse_listener() {}

		virtual void on_mouse_enter(display::Window& window) = 0;
		virtual void on_mouse_leave(display::Window& window) = 0;
		virtual void on_mouse_move(display::Window& window, double x, double y) = 0;
		virtual void on_mouse_click(display::Window& window, int button, int action, int mods) = 0;
		virtual void on_mouse_scroll(display::Window& window, double x_offset, double y_offset) = 0;
	};
}


