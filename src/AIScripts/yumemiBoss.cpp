//
// Created by Gegel85 on 25/06/2020.
//

#include "../Core/ECS/Core.hpp"
#include "../Core/Resources/Map.hpp"
#include "../Core/Input/AiController.hpp"
#include "../Core/ECS/Components/AiComponent.hpp"
#include "../Core/ECS/Components/PositionComponent.hpp"

using AIResponse = TouhouFanGame::Inputs::AIController::AIResponse;
using Entity = TouhouFanGame::ECS::Entity;

struct State {
	unsigned timer;
};

AIResponse makeAIDecision(State &state, Entity &me, TouhouFanGame::ECS::Core &core, TouhouFanGame::Map &map)
{
	state.timer = 3500;
	return {
		0,
		{
			TouhouFanGame::Input::USE_CARD
		}
	};
}

extern "C"
{
	State *makeUserData()
	{
		return new State{
			0
		};
	}

	void deleteUserData(State *data)
	{
		delete data;
	}

	AIResponse getAIActions(State *state, Entity &me, TouhouFanGame::ECS::Core &core, TouhouFanGame::Map &map) {
		if (state->timer > 0)
			return state->timer--, AIResponse{
				0,
				{}
			};
		return makeAIDecision(*state, me, core, map);
	}
}