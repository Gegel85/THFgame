//
// Created by Gegel85 on 16/04/2020.
//

#ifndef THFGAME_CUTSCENECOMPONENT_HPP
#define THFGAME_CUTSCENECOMPONENT_HPP


#include <memory>
#include "../Component.hpp"
#include "../../ExternalCode/ExternalModule.hpp"

namespace TouhouFanGame
{
	class Game;
}

namespace TouhouFanGame::ECS::Components
{
	class CutsceneComponent : public Component {
	private:
		std::string _modulePath;

	public:
		Game &game;
		std::unique_ptr<ExternalModule> handler;
		bool triggered = false;
		bool isProgress = false;

		CutsceneComponent(Game &game, std::istream &stream);
		CutsceneComponent(Game &game, const std::string &modulePath);
		~CutsceneComponent() override = default;
		void serialize(std::ostream &) const override;
	};
}


#endif //THFGAME_CUTSCENECOMPONENT_HPP
