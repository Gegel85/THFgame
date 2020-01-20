//
// Created by Gegel85 on 09/12/2019.
//

#include "ClassicItem.hpp"

namespace TouhouFanGame
{
	ClassicItem::ClassicItem(unsigned i, const nlohmann::json &obj) :
		Item(i, obj, true)
	{
	}

	void ClassicItem::_specialEffect(ECS::Entity &)
	{
	}
}