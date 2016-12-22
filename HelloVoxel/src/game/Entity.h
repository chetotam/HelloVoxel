#pragma once


namespace game
{
	// TODO: make more use of this class
	class Entity
	{
	public:
		virtual ~Entity() {}

		virtual void update(float dt) = 0;
	};
}

