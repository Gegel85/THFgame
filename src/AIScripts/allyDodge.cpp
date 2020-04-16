//
// Created by Gegel85 on 15/04/2020.
//

#include <vector>
#include "../Core/ECS/Core.hpp"
#include "../Core/Input/Input.hpp"
#include "../Core/Resources/Map.hpp"
#include "../Core/Input/AiController.hpp"

extern "C"
{
	TouhouFanGame::Inputs::AIController::AIResponse getAIActions(void *, TouhouFanGame::ECS::Core &, TouhouFanGame::Map &) {
		return {
			0,
			{}
		};
	}
}