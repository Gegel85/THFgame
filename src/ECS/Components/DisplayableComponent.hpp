//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_DISPLAYABLECOMPONENT_HPP
#define THFGAME_DISPLAYABLECOMPONENT_HPP


#include "../Component.hpp"
#include "../../Rendering/Entity.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief Given to Entity that can be displayed.
	class DisplayableComponent : public Component {
	private:
		//! @brief The path to the config file loaded.
		std::string _configPath;

	public:
		//! @brief The Rendering::Entity bound to this Entity.
		Rendering::Entity	&renderEntity;

		//! @brief The current Animation of the Entity.
		Rendering::Animation	animation{Rendering::IDLE};

		explicit DisplayableComponent(const std::string &configPath);
		~DisplayableComponent() override;
		void serialize(std::ostream &) const override;
		void unserialize(std::istream &) override;
	};
}


#endif //THFGAME_DISPLAYABLECOMPONENT_HPP
