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
		unsigned lifeTime;
		Entity *owner;
		std::vector<std::string> targets;
		std::unique_ptr<ExternalModule> effect;

		//! @brief Unserializer constructor.
		ProjectileComponent(Game &game, std::istream &stream);
		ProjectileComponent(Game &game, std::string modulePath, unsigned damages = 0, unsigned lifeTime = -1, Entity *entity = nullptr, const std::vector<std::string> &&targets = {});
		~ProjectileComponent() override;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_PROJECTILECOMPONENT_HPP
