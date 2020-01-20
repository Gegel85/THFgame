//
// Created by Gegel85 on 20/01/2020.
//

#ifndef THFGAME_EXPERIENCESYSTEM_HPP
#define THFGAME_EXPERIENCESYSTEM_HPP


#include "../System.hpp"

#define EXP_NEEDED 20

namespace TouhouFanGame::ECS::Systems
{
	//! @brief Updates Entity having a ExperienceSystemComponent
	class ExperienceSystem : public System {
	public:
		//! @param _parent The Core the System is in.
		explicit ExperienceSystem(Core &_parent);
		void updateEntity(const std::shared_ptr<Entity> &) override;
	};
}


#endif //THFGAME_EXPERIENCESYSTEM_HPP
