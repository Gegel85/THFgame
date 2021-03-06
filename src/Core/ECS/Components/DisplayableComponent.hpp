//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_DISPLAYABLECOMPONENT_HPP
#define THFGAME_DISPLAYABLECOMPONENT_HPP


#include "../Component.hpp"
#include "../../Rendering/Entity.hpp"

namespace TouhouFanGame
{
	struct Game;
	class ComponentGui;

	namespace ECS::Components {
		//! @brief Given to Entity that can be displayed.
		class DisplayableComponent : public Component {
		private:
			//! @brief The resources of the game.
			Resources &_resources;

			//! @brief The Screen the Rendering::Entity is in.
			Rendering::Screen &_screen;

			//! @brief The path to the config file loaded.
			std::string _configPath;

			friend ComponentGui;

		public:
			//! @brief The Rendering::Entity bound to this Entity.
			Rendering::Entity &renderEntity;

			//! @brief The current Animation of the Entity.
			Rendering::Animation animation{Rendering::IDLE};

			//! @brief Facing direction.
			Rendering::Direction dir = Rendering::NORTH;

			//! @brief Change the configs of this entity.
			void setConfigs(const std::string &path);

			//! @brief Unserializer constructor.
			explicit DisplayableComponent(Resources &resources, std::istream &stream);
			explicit DisplayableComponent(Resources &resources, const std::string &configPath);
			~DisplayableComponent() override;
			void serialize(std::ostream &) const override;
		};
	}
}


#endif //THFGAME_DISPLAYABLECOMPONENT_HPP
