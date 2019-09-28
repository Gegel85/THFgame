//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_CONTROLLABLECOMPONENT_HPP
#define THFGAME_CONTROLLABLECOMPONENT_HPP


#include "../Component.hpp"
#include "../../Input.hpp"

namespace TouhouFanGame::ECS::Components
{
	class ControllableComponent : public Component {
	public:
		Input &input;
		bool disabled = false;
		float regularSpeed;
		float sprintSpeed;

		explicit ControllableComponent(Input &input, float regularSpeed, float sprintSpeed);
		~ControllableComponent() override = default;
		void serialize(std::ostream &) const override;
		void unserialize(std::istream &) override;
	};
}


#endif //THFGAME_CONTROLLABLECOMPONENT_HPP
