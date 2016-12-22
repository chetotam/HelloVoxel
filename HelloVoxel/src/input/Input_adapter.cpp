#include "Input_adapter.h"


input::Input_adapter::Input_adapter() {}

input::Input_adapter::~Input_adapter() {}

void input::Input_adapter::on_window_iconify(display::Window& window) {}

void input::Input_adapter::on_window_restore(display::Window& window) {}

void input::Input_adapter::on_window_focus(display::Window& window) {}

void input::Input_adapter::on_window_defocus(display::Window& window) {}

void input::Input_adapter::on_window_move(display::Window& window, int x, int y) {}

void input::Input_adapter::on_window_resize(display::Window& window, int width, int height) {}

void input::Input_adapter::on_window_close(display::Window& window) {}

void input::Input_adapter::on_mouse_enter(display::Window& window) {}

void input::Input_adapter::on_mouse_leave(display::Window& window) {}

void input::Input_adapter::on_mouse_move(display::Window& window, double x, double y) {}

void input::Input_adapter::on_mouse_click(
	display::Window& window, int button, int action, int mods) {}

void input::Input_adapter::on_mouse_scroll(
	display::Window& window, double x_offset, double y_offset) {}

void input::Input_adapter::on_key_press(
	display::Window& window, int key, int scancode, int action, int mods) {}
