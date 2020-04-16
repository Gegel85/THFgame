//
// Created by Gegel85 on 16/04/2020.
//

#ifndef THFGAME_AICOMPONENT_HPP
#define THFGAME_AICOMPONENT_HPP


#include "ControllableComponent.hpp"
#include "../../Input/AiController.hpp"

namespace TouhouFanGame::ECS::Components
{
	class AIComponent  : public ControllableComponent {
	private:
		Inputs::AIController _ai;

	public:
		//! @brief Unserializer constructor.
		AIComponent(std::istream &stream, Map &map, ECS::Core &core);
		AIComponent(const std::string &modulePath, float regularSpeed, float sprintSpeed, Map &map, ECS::Core &core);
		~AIComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_AICOMPONENT_HPP
