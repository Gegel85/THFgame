//
// Created by Gegel85 on 28/04/2020.
//

#ifndef THFGAME_COLLIDERGUI_HPP
#define THFGAME_COLLIDERGUI_HPP


#include <TGUI/TGUI.hpp>
#include "../Core/ECS/Quadtree/ICollider.hpp"
#include "../Core/ECS/Quadtree/RectangleCollider.hpp"
#include "../Core/ECS/Quadtree/CircleCollider.hpp"

namespace TouhouFanGame
{
	class ColliderGui {
	private:
		static const std::map<std::string, std::function<tgui::Panel::Ptr(ECS::Quadtree::ICollider &)>> _builder;

		static tgui::Panel::Ptr _makePanel(const std::string &name, ECS::Quadtree::ICollider &collider);

		static tgui::Panel::Ptr CircleGui(ECS::Quadtree::ICollider &collider);
		static tgui::Panel::Ptr RectangleGui(ECS::Quadtree::ICollider &collider);

	public:
		static tgui::Panel::Ptr makePanel(ECS::Entity &entity, std::unique_ptr<ECS::Quadtree::ICollider> &collider);
	};
}


#endif //THFGAME_COLLIDERGUI_HPP
