#include "glad\glad.h";
#include "display\GLFW_window.h"

#include "game\Game.h"

#include <GLFW\glfw3.h>;
#include <iostream>


int main() {
	// TODO: hide glfw stuff somewhere?
	// mb use some kind of Application class to handle this
	if (glfwInit() != GL_TRUE) {
		std::cerr << "Unable to initialize GLFW\n";
		return 1;
	}

	game::Game voxel_game;
	voxel_game.start();

	glfwTerminate();
}
// yo