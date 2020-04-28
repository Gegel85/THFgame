//
// Created by Gegel85 on 28/04/2020.
//

#include "../Core/ECS/Exceptions.hpp"
#include "ColliderGui.hpp"
#include "../Core/Utils/Utils.hpp"
#include "../Core/ECS/Quadtree/ColliderFactory.hpp"

namespace TouhouFanGame
{
	const std::map<std::string, std::function<tgui::Panel::Ptr(ECS::Quadtree::ICollider &)>> ColliderGui::_builder{
		{"Circle", CircleGui},
		{"Rectangle", RectangleGui}
	};

	tgui::Panel::Ptr ColliderGui::_makePanel(const std::string &name, ECS::Quadtree::ICollider &collider)
	{
		try {
			return ColliderGui::_builder.at(name)(collider);
		} catch (std::out_of_range &) {
			throw ECS::InvalidColliderException("Invalid collider name \"" + name + "\"");
		}
	}

	tgui::Panel::Ptr ColliderGui::makePanel(ECS::Entity &entity, std::unique_ptr<ECS::Quadtree::ICollider> &collider)
	{
		auto panel = tgui::ScrollablePanel::create();
		auto colliderSpecificPanel = ColliderGui::_makePanel(collider->getName(), *collider);

		panel->loadWidgetsFromFile("assets/gui/ICollider.txt");
		collider->setOrigin(entity.getComponent(Position).position);

		auto originX = panel->get<tgui::EditBox>("OffsetX");
		auto originY = panel->get<tgui::EditBox>("OffsetY");
		auto shape = panel->get<tgui::EditBox>("Shape");
		auto angle = panel->get<tgui::EditBox>("Angle");
		auto error = panel->get<tgui::Label>("Error");

		shape->setText(collider->getName());
		angle->setText(Utils::floatToString(collider->getRotation()));
		originX->setText(Utils::floatToString(collider->getOffset().x));
		originY->setText(Utils::floatToString(collider->getOffset().y));

		shape->connect("TextChanged", [&collider, shape, error, panel, &entity]{
			try {
				if (collider->getName() == shape->getText())
					return;
				collider.reset(ECS::Quadtree::ColliderFactory::build(shape->getText()));
				collider->setOrigin(entity.getComponent(Position).position);
				error->setText("");

				auto otherPanel = ColliderGui::_makePanel(collider->getName(), *collider);

				otherPanel->setPosition(0, 90);
				error->setPosition(0, 100 + otherPanel->getSize().y);
				panel->setSize({300, 160 + otherPanel->getSize().y});
				panel->remove(panel->get<tgui::Widget>("SpecificPanel"));
				panel->add(otherPanel, "SpecificPanel");
				panel->setSize({300, 160 + otherPanel->getSize().y});
			} catch (std::exception &e) {
				error->setText(getLastExceptionName() + "\n" + e.what());
			}
		});
		angle->connect("TextChanged", [&collider, angle]{
			try {
				collider->setRotation(std::stof(static_cast<std::string>(angle->getText())));
			} catch (std::invalid_argument &) {}
		});
		originX->connect("TextChanged", [&collider, originX](){
			try {
				collider->setOffset({
					std::stof(static_cast<std::string>(originX->getText())),
					collider->getOffset().y
				});
			} catch (std::invalid_argument &) {}
		});
		originY->connect("TextChanged", [&collider, originY](){
			try {
				collider->setOffset({
					collider->getOffset().x,
					std::stof(static_cast<std::string>(originY->getText()))
				});
			} catch (std::invalid_argument &) {}
		});

		colliderSpecificPanel->setPosition(0, 90);
		error->setPosition(0, 100 + colliderSpecificPanel->getSize().y);
		panel->setSize({300, 160 + colliderSpecificPanel->getSize().y});
		panel->add(colliderSpecificPanel, "SpecificPanel");
		return panel;
	}

	tgui::Panel::Ptr ColliderGui::CircleGui(ECS::Quadtree::ICollider &collider)
	{
		auto &col = dynamic_cast<ECS::Quadtree::CircleCollider &>(collider);
		auto panel = tgui::Panel::create({300, 30});

		panel->loadWidgetsFromFile("assets/gui/CircleCollider.txt");

		auto radiusBox = panel->get<tgui::EditBox>("Radius");

		radiusBox->setText(Utils::floatToString(col.radius));
		radiusBox->connect("TextChanged", [&col, radiusBox]{
			if (!radiusBox->getText().isEmpty())
				col.setRadius(std::stof(static_cast<std::string>(radiusBox->getText())));
		});
		return panel;
	}

	tgui::Panel::Ptr ColliderGui::RectangleGui(ECS::Quadtree::ICollider &collider)
	{
		auto &col = dynamic_cast<ECS::Quadtree::RectangleCollider &>(collider);
		auto panel = tgui::Panel::create({300, 30});

		panel->loadWidgetsFromFile("assets/gui/RectangleCollider.txt");

		auto sizeXBox = panel->get<tgui::EditBox>("SizeX");
		auto sizeYBox = panel->get<tgui::EditBox>("SizeY");

		sizeXBox->setText(Utils::floatToString(col.getSize().x));
		sizeYBox->setText(Utils::floatToString(col.getSize().y));
		sizeXBox->connect("TextChanged", [&col, sizeXBox]{
			if (!sizeXBox->getText().isEmpty())
				col.setSize(Vector2<unsigned>(
					std::stoul(static_cast<std::string>(sizeXBox->getText())),
					col.getSize().y
				));
		});
		sizeYBox->connect("TextChanged", [&col, sizeYBox]{
			if (!sizeYBox->getText().isEmpty())
				col.setSize(Vector2<unsigned>(
					col.getSize().x,
					std::stoul(static_cast<std::string>(sizeYBox->getText()))
				));
		});
		return panel;
	}
}