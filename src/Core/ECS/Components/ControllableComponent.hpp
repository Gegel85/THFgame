//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_CONTROLLABLECOMPONENT_HPP
#define THFGAME_CONTROLLABLECOMPONENT_HPP


#include "../Component.hpp"
#include "../../Input/Input.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief Given to Entity that can be controlled.
	class ControllableComponent : public Component {
	protected:
		ControllableComponent(const std::string &name, Input &input, float regularSpeed, float sprintSpeed);
		ControllableComponent(const std::string &name, Input &input, std::istream &stream);

	public:
		//! @brief The Input device controlling this Entity.
		Input &input;

		//! @brief Whether the controls are disabled or not.
		bool disabled = false;

		//! @brief The base speed.
		float regularSpeed;

		//! @brief The speed when sprinting.
		float sprintSpeed;

		//! @brief Unserializer constructor.
		ControllableComponent(Input &input, std::istream &stream);
		ControllableComponent(Input &input, float regularSpeed, float sprintSpeed);
		~ControllableComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_CONTROLLABLECOMPONENT_HPP
