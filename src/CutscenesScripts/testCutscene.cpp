//
// Created by Gegel85 on 16/04/2020.
//


#include "../Core/Resources/Game.hpp"
#include "../Core/ECS/Components/PositionComponent.hpp"

extern "C"
{
	//! @brief Called when module is loaded.
	//! @return A new userdata passed as first parameter to all other module function.
	void *makeUserData()
	{
		return malloc(1);
	}

	//! @brief Called when module is unloaded
	//! @param data The user data returned by makeUserData
	void deleteUserData(void *data)
	{
		free(data);
	}

	bool isConditionCompleted(void *, TouhouFanGame::ECS::Entity &, TouhouFanGame::Game &)
	{
		return true;
	}

	void start(void *, TouhouFanGame::ECS::Entity &, TouhouFanGame::Game &game)
	{
		auto entity = game.state.map.getECSCore().makeEntity("TestAlly").lock();

		entity->getComponent(Position).position = game.state.map.getPlayer()->getComponent(Position).position;
	}

	void update(void *)
	{

	}

	bool isCompleted(void *)
	{
		return true;
	}
}