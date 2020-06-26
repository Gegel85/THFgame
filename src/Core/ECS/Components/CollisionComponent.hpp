//
// Created by Gegel85 on 05/01/2020.
//

#ifndef THFGAME_COLLISIONCOMPONENT_HPP
#define THFGAME_COLLISIONCOMPONENT_HPP


#include <memory>
#include "BasicSerializeComponent.hpp"
#include "../Entity.hpp"
#include "../Quadtree/ICollider.hpp"

namespace TouhouFanGame::ECS::Components
{
	class CollisionComponent : public Component {
	public:
		std::vector<std::unique_ptr<Quadtree::ICollider>> colliders;
		std::vector<std::pair<std::shared_ptr<ECS::Entity>, std::pair<unsigned, unsigned>>> collided;

		explicit CollisionComponent(std::istream &istream);
		explicit CollisionComponent(const std::vector<Quadtree::ICollider *> &colliders);
		void serialize(std::ostream &stream) const override;
		~CollisionComponent() override = default;
	};
}


#endif //THFGAME_COLLISIONCOMPONENT_HPP
