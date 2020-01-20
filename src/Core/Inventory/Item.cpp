//
// Created by Gegel85 on 08/12/2019.
//

#include "Item.hpp"
#include "../ECS/Components/HealthComponent.hpp"
#include "../ECS/Components/ManaComponent.hpp"

namespace TouhouFanGame
{
	Item::Item(unsigned index, nlohmann::json obj, bool usable) :
		_index(index),
		_usable(usable),
		_name(         obj["name"].is_null()                  ? "" : obj["name"]),
		_texture(      obj["icon"].is_null()                  ? "" : obj["icon"]),
		_description(  obj["description"].is_null()           ? "" : obj["description"]),
		_abilityScript(obj["effects"]["ability"].is_null()    ? "" : obj["effects"]["ability"]),
		_mana(         obj["effects"]["mana"].is_null()       ? 0  : obj["effects"]["mana"]      .get<int>()),
		_maxMana(      obj["effects"]["max_mana"].is_null()   ? 0  : obj["effects"]["max_mana"]  .get<int>()),
		_life(         obj["effects"]["healing"].is_null()    ? 0  : obj["effects"]["healing"]   .get<int>()),
		_maxLife(      obj["effects"]["max_health"].is_null() ? 0  : obj["effects"]["max_health"].get<int>())
	{
	}

	void Item::use(TouhouFanGame::ECS::Entity &entity)
	{
		auto &mana = entity.getComponent("Mana").to<ECS::Components::ManaComponent>();
		auto &health = entity.getComponent("Health").to<ECS::Components::HealthComponent>();

		mana.mana += this->_mana;
		mana.maxMana += this->_maxMana;
		health.health += this->_life;
		health.maxHealth += this->_maxLife;

		this->_specialEffect(entity);
	}

	unsigned Item::getIndex() const
	{
		return this->_index;
	}

	const std::string &Item::getName() const
	{
		return _name;
	}

	const std::string &Item::getTexture() const
	{
		return _texture;
	}

	const std::string &Item::getDescription() const
	{
		return _description;
	}

	const std::string &Item::getAbilityScript() const
	{
		return _abilityScript;
	}

	int Item::getMana() const
	{
		return _mana;
	}

	int Item::getMaxMana() const
	{
		return _maxMana;
	}

	int Item::getLife() const
	{
		return _life;
	}

	int Item::getMaxLife() const
	{
		return _maxLife;
	}
}