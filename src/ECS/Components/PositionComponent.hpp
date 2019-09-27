//
// Created by Gegel85 on 26/09/2019.
//

#ifndef THFGAME_POSITIONCOMPONENT_HPP
#define THFGAME_POSITIONCOMPONENT_HPP


#include <SFML/Graphics.hpp>
#include "../Component.hpp"

namespace TouhouFanGame::ECS::Components
{
	class PositionComponent : public ECS::Component {
	public:
		sf::Vector2f	position{0, 0};
		sf::Vector2u	size;

		PositionComponent(sf::Vector2u size);
		~PositionComponent() override = default;
		void serialize(std::ostream &) const override;
		void unserialize(std::istream &) override;
	};
}


#endif //THFGAME_POSITIONCOMPONENT_HPP
