//
// Created by Gegel85 on 09/12/2019.
//

#include "ItemFactory.hpp"
#include "../Exceptions.hpp"
#include "ClassicItem.hpp"

namespace TouhouFanGame
{
	const std::map<std::string, std::function<Item *(unsigned, const nlohmann::json &)>> ItemFactory::_builders{
		{"Classic", [](unsigned i, const nlohmann::json &obj) { return new ClassicItem(i, obj); }}
	};

	Item* TouhouFanGame::ItemFactory::buildItem(unsigned id, const std::string &name, const nlohmann::json &obj)
	{
		try {
			return _builders.at(name)(id, obj);
		} catch (std::out_of_range &e) {
			throw ItemNotFoundException("Cannot build a " + name + "Item");
		}
	}
}