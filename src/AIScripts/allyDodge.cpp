//
// Created by Gegel85 on 15/04/2020.
//

#include "../Core/ECS/Core.hpp"
#include "../Core/Resources/Map.hpp"
#include "../Core/Input/AiController.hpp"
#include "../Core/ECS/Components/AiComponent.hpp"
#include "../Core/ECS/Components/PositionComponent.hpp"

using AIResponse = TouhouFanGame::Inputs::AIController::AIResponse;
using Entity = TouhouFanGame::ECS::Entity;

void followPlayer(AIResponse &response, Entity &me, const std::shared_ptr<Entity> &player)
{
	auto &ai = me.getComponent(AI);
	auto &myPos = me.getComponent(Position);
	auto playerPos = player->getComponent(Position);
	bool collide = true;
	float dist = 0;
	float angle = 0;

	if (myPos.position.x > playerPos.position.x + playerPos.size.x) {
		angle = M_PI;
		collide = false;
		dist = myPos.position.x - (playerPos.position.x + playerPos.size.x);
	}
	if (playerPos.position.x > myPos.position.x + myPos.size.x) {
		angle = 0;
		collide = false;
		dist = playerPos.position.x - (myPos.position.x + myPos.size.x);
	}
	if (myPos.position.y > playerPos.position.y + playerPos.size.y) {
		angle = -M_PI_4 * (collide + 1) - angle / 2;
		collide = false;
		dist = std::sqrt(std::pow(dist, 2) + std::pow(myPos.position.y - (playerPos.position.y + playerPos.size.y), 2));
	}
	if (playerPos.position.y > myPos.position.y + myPos.size.y) {
		angle = M_PI_4 * (collide + 1) + angle / 2;
		collide = false;
		dist = std::sqrt(std::pow(dist, 2) + std::pow(playerPos.position.y - (myPos.position.y + myPos.size.y), 2));
	}

	if (!collide) {
		response.actions.push_back(TouhouFanGame::Input::UP);
		response.direction = angle;
		if (ai.regularSpeed < dist)
			response.actions.push_back(TouhouFanGame::Input::SPRINT);
	}
}

extern "C"
{
	AIResponse getAIActions(void *, Entity &me, TouhouFanGame::ECS::Core &, TouhouFanGame::Map &map) {
		AIResponse response{
			0,
			{}
		};

		followPlayer(response, me, map.getPlayer());
		return response;
	}
}
