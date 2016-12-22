#pragma once

#include "../glad/glad.h"
#include "../glm/glm.hpp"


struct Fog
{
	glm::vec3 color;
	GLfloat density;
};

struct Directional_light
{
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class Scene
{
	glm::vec3 sky_color; // mb use skybox
	Directional_light sun;
	Fog fog;

public:
	Scene();
	virtual ~Scene();
};

