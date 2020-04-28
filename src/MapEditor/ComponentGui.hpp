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
		static std::map<std::string, std::function<tgui::Panel::Ptr(Game &, ECS::Entity &, ECS::Component &)>> _builders;

		static tgui::Panel::Ptr MovableGui(ECS::Component &);
		static tgui::Panel::Ptr PositionGui(ECS::Entity &, ECS::Component &);
		static tgui::Panel::Ptr ControllableGui(ECS::Component &);
		static tgui::Panel::Ptr DisplayableGui(ECS::Component &);
		static tgui::Panel::Ptr ManaGui(ECS::Component &);
		static tgui::Panel::Ptr HealthGui(ECS::Component &);
		static tgui::Panel::Ptr NameGui(ECS::Component &);
		static tgui::Panel::Ptr EmptyGui();
		static tgui::Panel::Ptr InventoryGui(Game &, ECS::Component &);
		static tgui::Panel::Ptr DialogGui(ECS::Component &);
		static tgui::Panel::Ptr ColliderGui(ECS::Entity &entity, ECS::Component &);
		static tgui::Panel::Ptr CollisionGui(ECS::Entity &entity, ECS::Component &);
		static tgui::Panel::Ptr ShootGui(ECS::Component &);
		static tgui::Panel::Ptr DeckGui(ECS::Component &);
		static tgui::Panel::Ptr CutsceneGui(ECS::Component &);
		static tgui::Panel::Ptr AIGui(ECS::Component &);
		static tgui::Panel::Ptr ExperienceGui(ECS::Component &);

	public:
		static tgui::Panel::Ptr build(Game &, ECS::Entity &entity, ECS::Component &component);
	};
}


#endif //THFGAME_COMPONENTGUI_HPP
