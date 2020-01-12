//
// Created by Gegel85 on 12/01/2020.
//

#ifndef THFGAME_SHOOTSYSTEM_HPP
#define THFGAME_SHOOTSYSTEM_HPP


#include "../System.hpp"

namespace TouhouFanGame::ECS::Systems
{
	class ShootSystem : public System {
	public:
		ShootSystem(Core &core);
		void updateEntity(const std::shared_ptr<Entity> &) override;
	};
}


#endif //THFGAME_SHOOTSYSTEM_HPP
