//
// Created by Gegel85 on 26/09/2019.
//

#ifndef THFGAME_POSITIONCOMPONENT_HPP
#define THFGAME_POSITIONCOMPONENT_HPP


#include <SFML/Graphics.hpp>
#include "../Component.hpp"

namespace TouhouFanGame::ECS::Components
{
	//! @brief Given to Entity that exists somewhere
	class PositionComponent : public ECS::Component {
	public:
		//! @brief The position of the Entity
		sf::Vector2f	position{0, 0};

		//! @brief The size of the Entity
		sf::Vector2u	size;

		//! @brief Unserializer constructor.
		PositionComponent(std::istream &stream);
		PositionComponent(sf::Vector2u size);
		~PositionComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_POSITIONCOMPONENT_HPP
