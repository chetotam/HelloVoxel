#pragma once

#include "../graphics/Renderer.h"
#include "../display/GLFW_window.h"
#include "../input/Input_manager.h"
#include "../game/Level.h"

class Window;


namespace game
{
	// TODO: Maybe separate game class in some kind of engine class to handle rendering / input stuff
	// and bunch of game states to be able to switch between actual game and different menus
	class Game
	{
		display::GLFW_window window;
		graphics::Renderer renderer;
		input::Input_manager input;

		bool running;
		bool paused;

		game::Level level;

	public:
		Game();
		~Game();

		void start();
		void stop();
		void pause();
		void resume();

		display::GLFW_window& get_window();
		graphics::Renderer& get_renderer();
		input::Input_manager& get_input();

	private:
		void update(float dt);
		void render();
	};
}


