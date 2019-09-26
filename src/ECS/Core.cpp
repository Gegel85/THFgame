//
// Created by Gegel85 on 27/09/2019.
//

#include "Core.hpp"

namespace TouhouFanGame::ECS
{
	void Core::update()
	{
		for (auto &entity : this->_entities)
			entity->update();
	}

	void Core::clear()
	{
		this->_entities.clear();
	}
}