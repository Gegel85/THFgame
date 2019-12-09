//
// Created by Gegel85 on 09/12/2019.
//

#include "ItemFactory.hpp"
#include "../../Exceptions.hpp"
#include "ClassicItem.hpp"

namespace TouhouFanGame
{
	const std::map<std::string, std::function<Item *(const nlohmann::json &)>> ItemFactory::_builders{
		{"Classic", [](const nlohmann::json &obj) { return new ClassicItem(obj); }}
	};

	Item* TouhouFanGame::ItemFactory::buildItem(const std::string &name, const nlohmann::json &obj)
	{
		try {
			return _builders.at(name)(obj);
		} catch (std::out_of_range &e) {
			throw ItemNotFoundException("Cannot build a " + name + "Item");
		}
	}
}