#pragma once

#include "../glad/glad.h"
#include "Program.h"

#include <vector>


// Hmmmm, could this be done another way?
// May I just include this?
// And do I need all this namespaces at all?
namespace display
{
	class Window;
}

namespace game
{
	class Voxel;
}

namespace graphics
{
	class Program;
	class Camera;
}


namespace graphics
{
	// TODO: Create another renderer without hardcoded stuff
	// and capable of rendering more abstract things then juct Voxel objects
	class Renderer
	{
		GLfloat aspect_ratio;
		GLfloat z_near{ 0.1f };
		GLfloat z_far{ 500.0f };

		Program program;	// I guess shader program should not be a part of this class
							// mb part of Entity? or some Render component?

	public:
		Renderer();
		~Renderer();
		void render(const display::Window& window, game::Voxel& mesh, Camera& cam, Program& program);
		void render(const display::Window& window, std::vector<game::Voxel>& voxels, Camera& cam);
	};
}


