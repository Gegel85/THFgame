//
// Created by Gegel85 on 12/10/2019.
//

#include "BlockedByTerrainComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	BlockedByTerrainComponent::BlockedByTerrainComponent(TouhouFanGame::Map &map) :
		BasicSerializeComponent("BlockedByTerrain"),
		map(map)
	{
	}
}