//
// Created by Gegel85 on 05/01/2020.
//

#ifndef THFGAME_COLLISIONSYSTEM_HPP
#define THFGAME_COLLISIONSYSTEM_HPP


#include "../System.hpp"
#include "../../Rendering/Screen.hpp"
//#include "../Quadtree/Quadtree.hpp"

namespace TouhouFanGame::ECS::Systems
{
	//! @brief Updates Entity having a CollisionComponent
	class CollisionSystem : public System {
	private:
		//Quadtree::Quadtree _quadtree;

	public:
		//! @param core The Core the System is in.
		explicit CollisionSystem(Core &core);
		void updateEntity(const std::shared_ptr<Entity> &entity) override;
		void update() override;
	};
}


#endif //THFGAME_COLLISIONSYSTEM_HPP
