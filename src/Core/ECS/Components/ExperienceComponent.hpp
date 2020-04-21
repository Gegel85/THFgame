//
// Created by Gegel85 on 20/01/2020.
//

#ifndef THFGAME_EXPERIENCECOMPONENT_HPP
#define THFGAME_EXPERIENCECOMPONENT_HPP


#include "../Component.hpp"

namespace TouhouFanGame::ECS::Components
{
	class ExperienceComponent : public Component {
	public:
		unsigned exp = 0;
		unsigned level = 0;

		ExperienceComponent();
		ExperienceComponent(std::istream &stream);
		~ExperienceComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_EXPERIENCECOMPONENT_HPP
