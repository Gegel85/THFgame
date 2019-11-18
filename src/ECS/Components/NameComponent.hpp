//
// Created by Gegel85 on 18/11/2019.
//

#ifndef THFGAME_NAMECOMPONENT_HPP
#define THFGAME_NAMECOMPONENT_HPP


#include "../Component.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief An Entity with a name.
	class NameComponent : public Component {
	public:
		//! @brief The name of the Entity
		std::string name;

		//! @brief Unserializer constructor.
		NameComponent(std::istream &stream);
		NameComponent(const std::string &name);
		~NameComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_NAMECOMPONENT_HPP
