//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_DISPLAYABLECOMPONENT_HPP
#define THFGAME_DISPLAYABLECOMPONENT_HPP


#include "../Component.hpp"
#include "../../Rendering/Entity.hpp"

namespace TouhouFanGame::ECS::Components
{
	class DisplayableComponent : public Component {
	private:
		std::string _configPath;

	public:
		Rendering::Entity	&renderEntity;
		Rendering::Animation	animation{Rendering::IDLE};

		explicit DisplayableComponent(const std::string &config);
		~DisplayableComponent() override;
		void serialize(std::ostream &) const override;
		void unserialize(std::istream &) override;
	};
}


#endif //THFGAME_DISPLAYABLECOMPONENT_HPP
