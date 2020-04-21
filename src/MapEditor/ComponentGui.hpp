//
// Created by Gegel85 on 29/12/2019.
//

#ifndef THFGAME_COMPONENTGUI_HPP
#define THFGAME_COMPONENTGUI_HPP

#include <map>
#include <functional>
#include <TGUI/TGUI.hpp>
#include "../Core/ECS/Component.hpp"
#include "../Core/Resources/Game.hpp"

namespace TouhouFanGame
{
	class ComponentGui {
	private:
		static std::map<std::string, std::function<tgui::Panel::Ptr(Game &, ECS::Component &)>> _builders;

		static tgui::Panel::Ptr MovableGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr PositionGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr ControllableGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr DisplayableGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr ManaGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr HealthGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr NameGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr EmptyGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr InventoryGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr DialogGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr ColliderGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr CollisionGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr ShootGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr DeckGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr CutsceneGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr AIGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr ExperienceGui(Game &, ECS::Component &);

	public:
		static tgui::Panel::Ptr build(Game &, ECS::Component &component);
	};
}


#endif //THFGAME_COMPONENTGUI_HPP
