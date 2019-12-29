//
// Created by Gegel85 on 29/12/2019.
//

#ifndef THFGAME_COMPONENTGUI_HPP
#define THFGAME_COMPONENTGUI_HPP

#include <map>
#include <functional>
#include <TGUI/TGUI.hpp>
#include "../Core/ECS/Component.hpp"

namespace TouhouFanGame
{
	class ComponentGui {
	private:
		static std::map<std::string, std::function<tgui::Panel::Ptr(ECS::Component &)>> _builders;

		static tgui::Panel::Ptr MovableGui(ECS::Component &);
		static tgui::Panel::Ptr PositionGui(ECS::Component &);
		static tgui::Panel::Ptr ControllableGui(ECS::Component &);
		static tgui::Panel::Ptr DisplayableGui(ECS::Component &);
		static tgui::Panel::Ptr BlockedByTerrainGui(ECS::Component &);
		static tgui::Panel::Ptr ManaGui(ECS::Component &);
		static tgui::Panel::Ptr HealthGui(ECS::Component &);
		static tgui::Panel::Ptr NameGui(ECS::Component &);
		static tgui::Panel::Ptr PlayerHUDGui(ECS::Component &);
		static tgui::Panel::Ptr InventoryGui(ECS::Component &);

	public:
		static tgui::Panel::Ptr build(ECS::Component &component);
	};
}


#endif //THFGAME_COMPONENTGUI_HPP
