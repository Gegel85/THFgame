//
// Created by Gegel85 on 09/12/2019.
//

#ifndef THFGAME_ITEMFACTORY_HPP
#define THFGAME_ITEMFACTORY_HPP


#include "Item.hpp"

namespace TouhouFanGame
{
	class ItemFactory {
	private:
		static const std::map<std::string, std::function<Item *(const nlohmann::json &)>> _builders;

	public:
		static Item *buildItem(const std::string &name, const nlohmann::json &obj);
	};
}


#endif //THFGAME_ITEMFACTORY_HPP
