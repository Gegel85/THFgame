//
// Created by Gegel85 on 28/04/2020.
//

#ifndef THFGAME_PROJECTILECOMPONENT_HPP
#define THFGAME_PROJECTILECOMPONENT_HPP


#include <vector>
#include <memory>
#include "../Component.hpp"
#include "../../ExternalCode/ExternalModule.hpp"
#include "../Entity.hpp"

namespace TouhouFanGame::ECS::Components
{
	class ProjectileComponent : public Component {
	private:
		std::string _modulePath;

	public:
		unsigned damages;
		std::weak_ptr<Entity> owner;
		std::vector<std::string> targets;
		std::unique_ptr<ExternalModule> effect;

		//! @brief Unserializer constructor.
		ProjectileComponent(std::istream &stream);
		ProjectileComponent(const std::string &modulePath, unsigned damages = 0,const std::weak_ptr<Entity> &entity = {}, const std::vector<std::string> &&targets = {});
		~ProjectileComponent() override;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_PROJECTILECOMPONENT_HPP
