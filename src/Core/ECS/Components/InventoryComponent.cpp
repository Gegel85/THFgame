//
// Created by Gegel85 on 21/12/2019.
//

#include "InventoryComponent.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame::ECS::Components
{
	InventoryComponent::InventoryComponent(unsigned maxSize) :
		Component("Inventory"),
		maxSize(maxSize)
	{}

	InventoryComponent::InventoryComponent(std::istream &stream, const std::vector<std::shared_ptr<Item>> &itemList) :
		Component("Inventory"),
		maxSize(0)
	{
		unsigned buf;

		stream >> this->maxSize >> buf;
		for (unsigned i = buf; i != 0; i--) {
			stream >> buf;
			if (buf >= itemList.size())
				throw InvalidSerializedString("There is no item loaded with id " + std::to_string(buf));
			this->items.push_back(itemList[buf]);
		}
	}

	void InventoryComponent::serialize(std::ostream &stream) const
	{
		stream << this->maxSize << " " << this->items.size();
		for (auto &item : this->items)
			stream << " " << item->getIndex();
	}

	bool InventoryComponent::addItem(const std::shared_ptr<Item> &item)
	{
		if (this->maxSize <= this->items.size())
			return false;
		this->items.push_back(item);
		return true;
	}
}