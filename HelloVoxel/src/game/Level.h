#pragma once

#include "Voxel.h"
#include "Player.h"
#include "../graphics/Mesh.h"
#include "../graphics/Program.h"

#include "../glm/glm.hpp"

#include <vector>
#include <array>
#include <random>

namespace game
{
	class Game;
}


namespace game
{
	class Level
	{
		game::Game& game;

		// Grid parameters
		// Grid is used to spawn entities uniformly
		const int rows{ 3 };
		const int cols{ 3 };
		float chunk_size{ 400.0f };
		std::array<std::array<glm::vec3, 3>, 3> grid; // TODO: Why can't create array from const?

		// Indexes for main tile
		// Player is placed on this tile and update method will track his movement from here
		int center_i{ 1 };
		int center_j{ 1 };

		int voxels_per_chunk{ 8 };
		int powerups_per_chunk{ 4 };

		// TODO: Use one vector for all entities
		Player player;
		std::vector<Voxel> tiles; // ground
		std::vector<Voxel> voxels; // obstacles
		std::vector<Voxel> powerups; // powerups
		// TODO: Make use of powerups;

		// Level data
		// Used to construct level objects in factory methods
		graphics::Mesh tile_mesh;
		graphics::Mesh voxel_mesh;
		graphics::Mesh powerup_mesh;

		// Level time is used to increase voxel count
		float time;

		// Random number generator to make random sized / located voxels
		std::random_device rd;
		std::mt19937 mt;
		std::uniform_real_distribution<float> pos_dist;
		std::uniform_real_distribution<float> size_dist;

	public:
		Level(Game& game);
		~Level();

		void update(float dt);
		void render();

		Game& get_game();
		Player get_player() const;
		// TODO: Create function returning vector of all level objects
		std::vector<Voxel>& get_tiles();
		std::vector<Voxel>& get_voxels();
		std::vector<Voxel>& get_powerups();

	private:
		void spawn_tile(glm::vec3 position);
		void spawn_voxel(glm::vec3 position);
		void spawn_powerup(glm::vec3 position);

		// Chunk? How do I call bunch of entities spawned around some point? (grid cells)
		void create_chunk(float x, float z);
		void create_empty_chunk(float x, float z);

		bool out_of_bounds(glm::vec3 point);
	};
}