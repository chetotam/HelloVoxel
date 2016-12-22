#pragma once

namespace display
{
	class Window;
}


namespace input
{
	class Keyboard_listener
	{
	public:
		virtual ~Keyboard_listener() {}

		virtual void on_key_press(
			display::Window& window, int key, int scancode, int action, int mods) = 0;
	};
}


