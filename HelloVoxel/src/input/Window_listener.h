#pragma once

namespace display
{
	class Window;
}


namespace input
{
	class Window_listener {
	public:
		virtual ~Window_listener() {}

		virtual void on_window_iconify(display::Window& window) = 0;
		virtual void on_window_restore(display::Window& window) = 0;
		virtual void on_window_focus(display::Window& window) = 0;
		virtual void on_window_defocus(display::Window& window) = 0;
		virtual void on_window_move(display::Window& window, int x, int y) = 0;
		virtual void on_window_resize(display::Window& window, int width, int height) = 0;
		virtual void on_window_close(display::Window& window) = 0;
	};
}
