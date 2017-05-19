#include "GLFW_window.h"

#include "../input/Window_listener.h"
#include "../input/Mouse_listener.h"
#include "../input/Keyboard_listener.h"

#include <iostream>


display::GLFW_window::GLFW_window(int width, int height, std::string title)
	: width(width), height(height), title(title)
{
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4); // This better be part of Renderer class

	handle = glfwCreateWindow(width, height, "", nullptr, nullptr);
	if (handle == nullptr) {
		//This maybe should throw an exception
		std::cerr << "Failed to create the GLFW window\n";
	}

	glfwSetWindowUserPointer(handle, this);

	// TODO: Check for nullptr in every callback?
	// TODO: How do I prevent dangling poiners here?
	// Create and set callbacks for window events
	GLFWwindowclosefun close_callback = [](GLFWwindow* w) {
		display::GLFW_window* window =
			reinterpret_cast<display::GLFW_window*>(glfwGetWindowUserPointer(w));
		for (input::Window_listener* listener : window->window_listeners) {
			listener->on_window_close(*window);
		}
	};
	GLFWwindowiconifyfun iconify_callback = [](GLFWwindow* w, int iconified) {
		display::GLFW_window* window =
			reinterpret_cast<display::GLFW_window*>(glfwGetWindowUserPointer(w));
		for (input::Window_listener* listener : window->window_listeners) {
			if (iconified) {
				listener->on_window_iconify(*window);
			}
			else {
				listener->on_window_restore(*window);
			}
		}
	};
	GLFWwindowfocusfun focus_callback = [](GLFWwindow* w, int focused) {
		display::GLFW_window* window =
			reinterpret_cast<display::GLFW_window*>(glfwGetWindowUserPointer(w));
		for (input::Window_listener* listener : window->window_listeners) {
			if (focused) {
				listener->on_window_focus(*window);
			}
			else {
				listener->on_window_defocus(*window);
			}
		}
	};
	GLFWwindowsizefun size_callback = [](GLFWwindow* w, int width, int height) {
		display::GLFW_window* window =
			reinterpret_cast<display::GLFW_window*>(glfwGetWindowUserPointer(w));
		for (input::Window_listener* listener : window->window_listeners) {
			listener->on_window_resize(*window, width, height);
		}
		window->width = width;
		window->height = height;
	};
	GLFWwindowposfun position_callback = [](GLFWwindow* w, int x, int y) {
		display::GLFW_window* window =
			reinterpret_cast<display::GLFW_window*>(glfwGetWindowUserPointer(w));
		for (input::Window_listener* listener : window->window_listeners) {
			listener->on_window_move(*window, x, y);
		}
		window->x = x;
		window->y = y;
	};

	glfwSetWindowCloseCallback(handle, close_callback);
	glfwSetWindowIconifyCallback(handle, iconify_callback);
	glfwSetWindowFocusCallback(handle, focus_callback);
	glfwSetWindowSizeCallback(handle, size_callback);
	glfwSetWindowPosCallback(handle, position_callback);

	// Create and set callbacks for mouse events
	GLFWcursorenterfun cursor_enter_callback = [](GLFWwindow* w, int entered) {
		display::GLFW_window* window =
			reinterpret_cast<display::GLFW_window*>(glfwGetWindowUserPointer(w));
		for (input::Mouse_listener* listener : window->mouse_listeners) {
			if (entered) {
				listener->on_mouse_enter(*window);
			}
			else {
				listener->on_mouse_leave(*window);
			}
		}
	};
	GLFWcursorposfun cursor_pos_callback = [](GLFWwindow* w, double x, double y) {
		display::GLFW_window* window =
			reinterpret_cast<display::GLFW_window*>(glfwGetWindowUserPointer(w));
		for (input::Mouse_listener* listener : window->mouse_listeners) {
			listener->on_mouse_move(*window, x, y);
		}
	};
	GLFWmousebuttonfun mouse_button_callback = [](GLFWwindow* w, int button, int action, int mods) {
		display::GLFW_window* window =
			reinterpret_cast<display::GLFW_window*>(glfwGetWindowUserPointer(w));
		for (input::Mouse_listener* listener : window->mouse_listeners) {
			listener->on_mouse_click(*window, button, action, mods);
		}
	};
	GLFWscrollfun mouse_scroll_callback = [](GLFWwindow* w, double x_offset, double y_offset) {
		display::GLFW_window* window =
			reinterpret_cast<display::GLFW_window*>(glfwGetWindowUserPointer(w));
		for (input::Mouse_listener* listener : window->mouse_listeners) {
			listener->on_mouse_scroll(*window, x_offset, y_offset);
		}
	};

	glfwSetCursorEnterCallback(handle, cursor_enter_callback);
	glfwSetCursorPosCallback(handle, cursor_pos_callback);
	glfwSetMouseButtonCallback(handle, mouse_button_callback);
	glfwSetScrollCallback(handle, mouse_scroll_callback);

	// Create and set callbacks for keyboard events
	GLFWkeyfun key_callback = [](GLFWwindow* w, int key, int scancode, int action, int mods) {
		display::GLFW_window* window =
			reinterpret_cast<display::GLFW_window*>(glfwGetWindowUserPointer(w));
		for (input::Keyboard_listener* listener : window->keyboard_listeners) {
			listener->on_key_press(*window, key, scancode, action, mods);
		}
	};
	glfwSetKeyCallback(handle, key_callback);

	// TODO: Move GL related function calls to renderer?
	glfwMakeContextCurrent(handle);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// TODO: Create separete method to handle cursor modes
	glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

display::GLFW_window::~GLFW_window()
{
	close();
}

void display::GLFW_window::close()
{
	if (handle != nullptr) {
		glfwDestroyWindow(handle);
	}
}

GLFWwindow * display::GLFW_window::get_handle() const
{
	return handle;
}

int display::GLFW_window::get_x() const
{
	// TODO: make this return real value
	return x;
}

int display::GLFW_window::get_y() const
{
	// TODO: make this return real value
	return y;
}

int display::GLFW_window::get_width() const
{
	return width;
}

int display::GLFW_window::get_height() const
{
	return height;
}

std::string display::GLFW_window::get_title() const
{
	return title;
}

void display::GLFW_window::set_x(int x)
{
	this->x = x;
	glfwSetWindowPos(handle, x, y);
}

void display::GLFW_window::set_y(int y)
{
	this->y = y;
	glfwSetWindowPos(handle, x, y);
}

void display::GLFW_window::set_width(int width)
{
	this->width = width;
	glfwSetWindowSize(handle, width, height);
}

void display::GLFW_window::set_height(int height)
{
	this->height = height;
	glfwSetWindowSize(handle, width, height);
}

void display::GLFW_window::set_title(std::string title)
{
	this->title = title;
	glfwSetWindowTitle(handle, title.c_str());
}

void display::GLFW_window::add_window_listener(input::Window_listener* listener)
{
	window_listeners.push_back(listener);
}

void display::GLFW_window::add_mouse_listener(input::Mouse_listener* listener)
{
	mouse_listeners.push_back(listener);
}

void display::GLFW_window::add_keyboard_listener(input::Keyboard_listener* listener)
{
	keyboard_listeners.push_back(listener);
}
