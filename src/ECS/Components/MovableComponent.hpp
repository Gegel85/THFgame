//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_MOVABLECOMPONENT_HPP
#define THFGAME_MOVABLECOMPONENT_HPP


#include "../Component.hpp"
#include "../../Rendering/Entity.hpp"

#define TO_DIR(dir) (1U << dir)

namespace TouhouFanGame::ECS::Components
{
	//! @brief Given to Entity that can move.
	class MovableComponent : public Component {
	public:
		//! @brief The direction to move to.
		unsigned char	dir = 0;

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
