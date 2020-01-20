//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_MOVABLECOMPONENT_HPP
#define THFGAME_MOVABLECOMPONENT_HPP


#include "../Component.hpp"
#include "../../Rendering/Entity.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief Given to Entity that can move.
	class MovableComponent : public Component {
	public:
		//! @brief The direction to move to.
		double	angleDir = 0;

		//! @brief The speed moving at.
		float	speed = 0; //I AM SPEEEEEEEEEEEED

		explicit MovableComponent();
		//! @brief Unserializer constructor.
		explicit MovableComponent(std::istream &stream);
		~MovableComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_MOVABLECOMPONENT_HPP
