//
// Created by Gegel85 on 16/04/2020.
//


#include "../Core/Resources/Game.hpp"

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

	bool isConditionCompleted(void *, TouhouFanGame::ECS::Entity &me, TouhouFanGame::Game &game)
	{
		return false;
	}

	void start(void *, TouhouFanGame::ECS::Entity &me, TouhouFanGame::Game &game)
	{

	}

	void update(void *)
	{

	}

	bool isCompleted(void *)
	{
		return true;
	}
}