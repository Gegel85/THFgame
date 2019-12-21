//
// Created by Gegel85 on 21/12/2019.
//

#ifndef THFGAME_INVENTORYCOMPONENT_HPP
#define THFGAME_INVENTORYCOMPONENT_HPP


#include "../Component.hpp"
#include "../../Inventory/Item.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief For Entity that can hold items.
	class InventoryComponent : public Component {
	public:
		//! @brief The number of items the entity can hold.
		unsigned maxSize;

		//! @brief The items in the inventory.
		std::vector<std::shared_ptr<Item>> items;

		//! @brief Adds an item to the inventory if it can fit.
		//! @return Whether the item has been inserted or not.
		bool addItem(const std::shared_ptr<Item> &item);

		//! @brief Unserializer constructor.
		InventoryComponent(std::istream &stream, const std::vector<std::shared_ptr<Item>> &itemList);
		InventoryComponent(unsigned maxSize);
		~InventoryComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_INVENTORYCOMPONENT_HPP
