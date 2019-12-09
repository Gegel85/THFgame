//
// Created by Gegel85 on 09/12/2019.
//

#include "ClassicItem.hpp"

namespace TouhouFanGame
{
	ClassicItem::ClassicItem(const nlohmann::json &obj) :
		Item(obj)
	{
	}

	void ClassicItem::_specialEffect(ECS::Entity &)
	{
	}
}