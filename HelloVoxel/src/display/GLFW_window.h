#pragma once

#include "Window.h"

#include "../glad/glad.h"
#include <GLFW\glfw3.h>

#include <string>
#include <vector>
#include <memory>


namespace display
{
	class GLFW_window :
		public display::Window
	{
		GLFWwindow* handle;

		int x;
		int y;
		int height;
		int width;
		std::string title;

		std::vector<input::Window_listener*> window_listeners;
		std::vector<input::Mouse_listener*> mouse_listeners;
		std::vector<input::Keyboard_listener*> keyboard_listeners;

	public:
		GLFW_window(int width, int height, std::string title);
		~GLFW_window();

		virtual void close() override;

		GLFWwindow* get_handle() const;

		virtual int get_x() const override;
		virtual int get_y() const override;
		virtual int get_width() const override;
		virtual int get_height() const override;
		virtual std::string get_title() const override;

		virtual void set_x(int x) override;
		virtual void set_y(int y) override;
		virtual void set_width(int width) override;
		virtual void set_height(int height) override;
		virtual void set_title(std::string title) override;

		virtual void add_window_listener(input::Window_listener* listener) override;
		virtual void add_mouse_listener(input::Mouse_listener* listener) override;
		virtual void add_keyboard_listener(input::Keyboard_listener* listener) override;
	};
}


