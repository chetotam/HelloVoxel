#pragma once

#include <string>
#include <memory>

namespace input
{
	class Window_listener;
	class Mouse_listener;
	class Keyboard_listener;
}


namespace display
{
	class Window
	{
	public:
		virtual ~Window() {}

		virtual void close() = 0;
		// TODO: Add ability to iconify window and toggle fullscreen mode

		virtual int get_x() const = 0;
		virtual int get_y() const = 0;
		virtual int get_width() const = 0;
		virtual int get_height() const = 0;
		virtual std::string get_title() const = 0;

		virtual void set_x(int x) = 0;
		virtual void set_y(int y) = 0;
		virtual void set_width(int width) = 0;
		virtual void set_height(int height) = 0;
		virtual void set_title(std::string title) = 0;

		virtual void add_window_listener(input::Window_listener* listener) = 0;
		virtual void add_mouse_listener(input::Mouse_listener* listener) = 0;
		virtual void add_keyboard_listener(input::Keyboard_listener* listener) = 0;
		// TODO: Add ability to remove listeners (important!)
	};
}


