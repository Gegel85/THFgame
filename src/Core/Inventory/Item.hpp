//
// Created by Gegel85 on 08/12/2019.
//

#ifndef THFGAME_ITEM_HPP
#define THFGAME_ITEM_HPP


#include <json.hpp>
#include "../ECS/Entity.hpp"

namespace TouhouFanGame
{
	class Item {
	private:
		virtual void _specialEffect(ECS::Entity &entity) = 0;

	protected:
		std::string _name;
		std::string _texture;
		std::string _description;
		std::string _abilityScript;
		int _mana;
		int _maxMana;
		int _life;
		int _maxLife;

	public:
		const std::string &getName() const;
		const std::string &getTexture() const;
		const std::string &getDescription() const;
		const std::string &getAbilityScript() const;
		int getMana() const;
		int getMaxMana() const;
		int getLife() const;
		int getMaxLife() const;

	public:
		Item(nlohmann::json obj);
		void use(ECS::Entity &entity);
	};
}


#endif //THFGAME_ITEM_HPP
