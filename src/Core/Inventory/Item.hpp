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
		unsigned _index;

		virtual void _specialEffect(ECS::Entity &entity) = 0;

	protected:
		bool _usable;
		std::string _name;
		std::string _texture;
		std::string _description;
		std::string _abilityScript;
		int _mana;
		int _maxMana;
		int _life;
		int _maxLife;

	public:
		bool isUsable() const;
		unsigned getIndex() const;
		const std::string &getName() const;
		const std::string &getTexture() const;
		const std::string &getDescription() const;
		const std::string &getAbilityScript() const;
		int getMana() const;
		int getMaxMana() const;
		int getLife() const;
		int getMaxLife() const;

		Item(unsigned index, nlohmann::json obj, bool usable);
		void use(ECS::Entity &entity);
	};
}


#endif //THFGAME_ITEM_HPP
