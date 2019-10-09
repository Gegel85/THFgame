//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_MOVABLECOMPONENT_HPP
#define THFGAME_MOVABLECOMPONENT_HPP


#include "../Component.hpp"
#include "../../Rendering/Entity.hpp"

namespace TouhouFanGame::ECS::Components
{
	class MovableComponent : public Component {
	public:
		unsigned char	dir = 0;
		float		speed = 0; //I AM SPEEEEEEEEEEEED

		explicit MovableComponent();
		~MovableComponent() override = default;
		void serialize(std::ostream &) const override;
		void unserialize(std::istream &) override;
	};
}


#endif //THFGAME_MOVABLECOMPONENT_HPP
