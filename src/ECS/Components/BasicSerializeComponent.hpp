//
// Created by Gegel85 on 18/11/2019.
//

#ifndef THFGAME_BASICSERIALIZECOMPONENT_HPP
#define THFGAME_BASICSERIALIZECOMPONENT_HPP


#include "../Component.hpp"

namespace TouhouFanGame::ECS::Components
{
	class BasicSerializeComponent : public Component {
	public:
		BasicSerializeComponent(const std::string &name);
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_BASICSERIALIZECOMPONENT_HPP
