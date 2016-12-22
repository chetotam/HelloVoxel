#include "Level.h"

#include "../util/Mesh_util.h"
#include "Game.h"

#include <iostream>


game::Level::Level(game::Game& game) : game(game), player(*this)
{
	tile_mesh = util::gen_textured_cube(util::gen_black_cross_tex(256, 256, 248, 248, 248, 255));
	voxel_mesh = util::gen_textured_cube(util::gen_one_color_tex(16, 16, 230, 230, 230, 255));
	powerup_mesh = util::gen_textured_cube(util::gen_one_color_tex(16, 16, 255, 0, 0, 255));

	mt = std::mt19937(rd());
	pos_dist = std::uniform_real_distribution<float>(0.0f, chunk_size);
	size_dist = std::uniform_real_distribution<float>(4.0f, 16.0f);

	time = 0.0f;

	// set up initial chunk positions
	// they later will be used to spawn entities
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			grid[i][j].x = j * chunk_size;
			grid[i][j].z = i * chunk_size;
		}
	}

	// spawn initial entities in front of player (positive x direction)
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (i == rows - 1) {
				create_chunk(grid[i][j].x, grid[i][j].z);
			}
			else {
				create_empty_chunk(grid[i][j].x, grid[i][j].z);
			}
		}
	}
	
	// Place player to the negative x border of center tile
	player.set_position({ grid[center_i][center_j].x, 1.5f, grid[center_i][center_j].z - chunk_size / 2 });
}

game::Level::~Level()
{
}

void game::Level::update(float dt)
{
	for (Voxel& v : voxels) {
		v.update(dt);
	}
	for (Voxel& t : tiles) {
		t.update(dt);
	}
	player.update(dt);

	time += dt;
	if (time > 5) {
		voxels_per_chunk += 1;
		time = 0;
	}

	// If player crossed main tile border in positive z direction 
	if (player.getZ() > grid[center_i][center_j].z + (chunk_size / 2)) {
		for (int i = 1; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				grid[i - 1][j] = grid[i][j];
			}
		}
		for (int j = 0; j < cols; ++j) {
			grid[rows - 1][j].z += chunk_size;
			create_chunk(grid[rows - 1][j].x, grid[rows - 1][j].z);
		}
	}
	// If player crossed main tile border in negative z direction 
	if (player.getZ() < grid[center_i][center_j].z - (chunk_size / 2)) {
		for (int i = rows - 1; i > 0; --i) {
			for (int j = 0; j < cols; ++j) {
				grid[i][j] = grid[i - 1][j];
			}
		}
		for (int j = 0; j < cols; ++j) {
			grid[0][j].z -= chunk_size;
			create_chunk(grid[0][j].x, grid[0][j].z);
		}
	}
	// If player crossed main tile border in positive x direction 
	if (player.getX() > grid[center_i][center_j].x + (chunk_size / 2)) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols - 1; ++j) {
				grid[i][j] = grid[i][j + 1];
			}
		}
		for (int i = 0; i < rows; ++i) {
			grid[i][cols - 1].x += chunk_size;
			create_chunk(grid[i][cols - 1].x, grid[i][cols - 1].z);
		}
	}
	// If player crossed main tile border in negative x direction
	if (player.getX() < grid[center_i][center_j].x - (chunk_size / 2)) {
		for (int i = 0; i < rows; ++i) {
			for (int j = cols - 1; j > 0; --j) {
				grid[i][j] = grid[i][j - 1];
			}
		}
		for (int i = 0; i < rows; ++i) {
			grid[i][0].x -= chunk_size;
			create_chunk(grid[i][0].x, grid[i][0].z);
		}
	}
}

void game::Level::render()
{
}

void game::Level::spawn_tile(glm::vec3 position)
{
	// if some voxel fall out of level bounds we could just reuse it instead of creating new one
	for (Voxel& t : tiles) {
		if (out_of_bounds(t.get_position())) {
			t.set_position({ position.x, position.y - t.get_scale().y / 2, position.z });
			return;
		}
	}
	Voxel t(tile_mesh);
	t.set_scale({ chunk_size, 1, chunk_size });
	t.set_position({ position.x, position.y - t.get_scale().y / 2, position.z });
	tiles.push_back(t);
}

void game::Level::spawn_voxel(glm::vec3 position)
{
	// if some voxel fall out of level bounds we could just reuse it instead of creating new one
	for (Voxel& v : voxels) {
		if (out_of_bounds(v.get_position())) {
			v.set_scale({ size_dist(mt), size_dist(mt) * 4, size_dist(mt) });
			v.set_position({ position.x, position.y + v.get_scale().y / 2, position.z });
			return;
		}
	}
	Voxel v(voxel_mesh);
	v.set_scale({ size_dist(mt), size_dist(mt) * 4, size_dist(mt) });
	v.set_position({ position.x, position.y + v.get_scale().y / 2, position.z});
	voxels.push_back(v);
}

void game::Level::spawn_powerup(glm::vec3 position)
{
	// if some voxel fall out of level bounds we could just reuse it instead of creating new one
	for (Voxel& p : powerups) {
		if (out_of_bounds(p.get_position())) {
			p.set_position({ position.x, 1.5f, position.z });
			return;
		}
	}
	Voxel p(powerup_mesh);
	p.set_scale({ 1.0f, 1.0f, 1.0f });
	p.set_position({ position.x, 1.5f, position.z });
	powerups.push_back(p);
}

void game::Level::create_chunk(float x, float z)
{
	spawn_tile({ x, 0, z });
	for (int i = 0; i < voxels_per_chunk; ++i) {
		spawn_voxel({ x + pos_dist(mt) - chunk_size / 2, 0.0f, z + pos_dist(mt) - chunk_size / 2 });
	}
	for (int i = 0; i < powerups_per_chunk; ++i) {
		spawn_powerup({ x + pos_dist(mt) - chunk_size / 2, 0.0f, z + pos_dist(mt) - chunk_size / 2 });
	}
}

void game::Level::create_empty_chunk(float x, float z)
{
	spawn_tile({ x, 0, z });
}

game::Game& game::Level::get_game()
{
	return game;
}

game::Player game::Level::get_player() const
{
	return player;
}

std::vector<game::Voxel>& game::Level::get_voxels()
{
	return voxels;
}

std::vector<game::Voxel>& game::Level::get_powerups()
{
	return powerups;
}

std::vector<game::Voxel>& game::Level::get_tiles()
{
	return tiles;
}

bool game::Level::out_of_bounds(glm::vec3 point)
{
	return
		point.z < grid[0][0].z - (chunk_size / 2) ||
		point.z > grid[rows - 1][0].z + (chunk_size / 2) ||
		point.x < grid[0][0].x - (chunk_size / 2) ||
		point.x > grid[0][cols - 1].x + (chunk_size / 2);
}

