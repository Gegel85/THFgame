//
// Created by Gegel85 on 26/09/2019.
//

#include "Entity.hpp"

namespace TouhouFanGame::ECS
{
	std::string Entity::getName()
	{
		return this->_name;
	}

	unsigned Entity::getID()
	{
		return this->_id;
	}

	void Entity::update()
	{
		//TODO: update
	}
}