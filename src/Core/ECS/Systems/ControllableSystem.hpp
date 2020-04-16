//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_CONTROLLABLESYSTEM_HPP
#define THFGAME_CONTROLLABLESYSTEM_HPP


#include "../System.hpp"
#include "../../Input/Input.hpp"
#include "../Components/ControllableComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	//! @brief Updates Entity having a ControllableComponent
	class ControllableSystem : public System {
	protected:
		void _updateEntity(const std::shared_ptr<Entity> &entity, Components::ControllableComponent &co);

	public:
		//! @param core The Core the System is in.
		ControllableSystem(Core &core, const std::string &&name = "Controllabe");
		void updateEntity(const std::shared_ptr<Entity> &entity) override;
	};
}


#endif //THFGAME_CONTROLLABLESYSTEM_HPP
