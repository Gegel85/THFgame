//
// Created by Gegel85 on 09/12/2019.
//

#ifndef THFGAME_CLASSICITEM_HPP
#define THFGAME_CLASSICITEM_HPP


#include "Item.hpp"

namespace TouhouFanGame
{
	class ClassicItem : public Item {
	private:
		void _specialEffect(ECS::Entity &entity) override;

	public:
		ClassicItem(unsigned id, const nlohmann::json &obj);
		~ClassicItem() override = default;
	};
}


#endif //THFGAME_CLASSICITEM_HPP
