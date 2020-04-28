//
// Created by Gegel85 on 29/12/2019.
//

#include "ComponentGui.hpp"
#include "GuiUtils.hpp"
#include "ColliderGui.hpp"
#include "../Core/ECS/Components/MovableComponent.hpp"
#include "../Core/ECS/Components/PositionComponent.hpp"
#include "../Core/Utils/Utils.hpp"
#include "../Core/ECS/Components/ControllableComponent.hpp"
#include "../Core/ECS/Components/DisplayableComponent.hpp"
#include "../Core/ECS/Components/BlockedByTerrainComponent.hpp"
#include "../Core/ECS/Components/ManaComponent.hpp"
#include "../Core/ECS/Components/HealthComponent.hpp"
#include "../Core/ECS/Components/NameComponent.hpp"
#include "../Core/ECS/Components/InventoryComponent.hpp"
#include "../Core/ECS/Components/DialogComponent.hpp"
#include "../Core/ECS/Components/CollisionComponent.hpp"
#include "../Core/ECS/Components/ColliderComponent.hpp"
#include "../Core/ECS/Components/CutsceneComponent.hpp"
#include "../Core/ECS/Components/AiComponent.hpp"
#include "../Core/ECS/Components/ShootComponent.hpp"
#include "../Core/ECS/Components/DeckComponent.hpp"
#include "../Core/ECS/Components/ExperienceComponent.hpp"
#include "../Core/ECS/Quadtree/ColliderFactory.hpp"

namespace TouhouFanGame
{
	std::map<std::string, std::function<tgui::Panel::Ptr(Game &, ECS::Entity &entity, ECS::Component &component)>> ComponentGui::_builders{
		{"Movable",          [](Game &    , ECS::Entity &      , ECS::Component &component){ return MovableGui(component);          }},
		{"Position",         [](Game &    , ECS::Entity &entity, ECS::Component &component){ return PositionGui(entity, component); }},
		{"Controllable",     [](Game &    , ECS::Entity &      , ECS::Component &component){ return ControllableGui(component);     }},
		{"Displayable",      [](Game &    , ECS::Entity &      , ECS::Component &component){ return DisplayableGui(component);      }},
		{"Mana",             [](Game &    , ECS::Entity &      , ECS::Component &component){ return ManaGui(component);             }},
		{"Health",           [](Game &    , ECS::Entity &      , ECS::Component &component){ return HealthGui(component);           }},
		{"Name",             [](Game &    , ECS::Entity &      , ECS::Component &component){ return NameGui(component);             }},
		{"Inventory",        [](Game &game, ECS::Entity &      , ECS::Component &component){ return InventoryGui(game, component);        }},
		{"Dialog",           [](Game &    , ECS::Entity &      , ECS::Component &component){ return DialogGui(component);           }},
		{"Collider",         [](Game &    , ECS::Entity &entity, ECS::Component &component){ return ColliderGui(entity, component);         }},
		{"Collision",        [](Game &    , ECS::Entity &entity, ECS::Component &component){ return CollisionGui(entity, component);        }},
		{"Cutscene",         [](Game &    , ECS::Entity &      , ECS::Component &component){ return CutsceneGui(component);         }},
		{"Deck",             [](Game &    , ECS::Entity &      , ECS::Component &component){ return DeckGui(component);             }},
		{"AI",               [](Game &    , ECS::Entity &      , ECS::Component &component){ return AIGui(component);               }},
		{"Shoot",            [](Game &    , ECS::Entity &      , ECS::Component &component){ return ShootGui(component);            }},
		{"Experience",       [](Game &    , ECS::Entity &      , ECS::Component &component){ return ExperienceGui(component);       }},
	};

	tgui::Panel::Ptr ComponentGui::CollisionGui(ECS::Entity &entity, ECS::Component &component)
	{
		auto &col = component.to<ECS::Components::CollisionComponent>();

		return ColliderGui::makePanel(entity, col.collider);
	}

	tgui::Panel::Ptr ComponentGui::ColliderGui(ECS::Entity &entity, ECS::Component &component)
	{
		auto &col = component.to<ECS::Components::ColliderComponent>();
		auto pos = 10;
		auto panel = tgui::ScrollablePanel::create({300, 100});

		if (col.colliders.empty())
			col.colliders.emplace_back(ECS::Quadtree::ColliderFactory::build("Rectangle"));

		for (auto &collider : col.colliders) {
			auto newPanel = ColliderGui::makePanel(entity, collider);

			//TODO: Add a way to add/delete colliders
			newPanel->setPosition({0, pos});
			pos += newPanel->getSize().y;
			panel->add(newPanel);
		}
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::MovableGui(ECS::Component &component)
	{
		auto &movable = component.to<ECS::Components::MovableComponent>();
		auto panel = tgui::Panel::create({300, 30});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto speedLabel = makeLabel("Speed", 0, 0);
		auto speedEditBox = makeTypeBox(
			speedLabel->getSize().x,
			0,
			60,
			speedLabel->getSize().y,
			Utils::floatToString(movable.speed),
			"[+-]?[0-9]*\\.?[0-9]*"
		);
		auto dirLabel = makeLabel("Dir", speedEditBox->getSize().x + speedEditBox->getPosition().x + 10, 0);
		auto dirEditBox = makeTypeBox(
			dirLabel->getSize().x + dirLabel->getPosition().x,
			0,
			60,
			speedLabel->getSize().y,
			Utils::floatToString(movable.angleDir),
			"[+-]?[0-9]*\\.?[0-9]*"
		);

		speedEditBox->connect("TextChanged", [&movable, speedEditBox]{
			if (!speedEditBox->getText().isEmpty())
				movable.speed = std::stof(speedEditBox->getText().toAnsiString());
		});
		dirEditBox->connect("TextChanged", [&movable, dirEditBox]{
			movable.angleDir = std::stof(dirEditBox->getText().toAnsiString());
		});
		panel->setRenderer(render);
		panel->add(speedLabel);
		panel->add(speedEditBox);
		panel->add(dirLabel);
		panel->add(dirEditBox);
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::PositionGui(ECS::Entity &entity, ECS::Component &component)
	{
		auto *collision = entity.hasComponent("Collision") ? &entity.getComponent(Collision) : nullptr;
		auto *collider = entity.hasComponent("Collider") ? &entity.getComponent(Collider) : nullptr;
		auto &position = component.to<ECS::Components::PositionComponent>();
		auto panel = tgui::Panel::create({300, 70});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto xLabel = makeLabel("Position X", 0, 0);
		auto xEditBox = makeTypeBox(
			xLabel->getSize().x,
			0,
			60,
			xLabel->getSize().y,
			Utils::floatToString(position.position.x),
			"[+-]?[0-9]*\\.?[0-9]*"
		);
		auto yLabel = makeLabel("Position Y", xEditBox->getSize().x + xEditBox->getPosition().x + 10, 0);
		auto yEditBox = makeTypeBox(
			yLabel->getSize().x + yLabel->getPosition().x,
			0,
			60,
			xLabel->getSize().y,
			Utils::floatToString(position.position.y),
			"[+-]?[0-9]*\\.?[0-9]*"
		);
		auto xSizeLabel = makeLabel("Size X", 0, xLabel->getSize().y);
		auto xSizeEditBox = makeTypeBox(
			xLabel->getSize().x,
			xLabel->getSize().y,
			60,
			xLabel->getSize().y,
			Utils::floatToString(position.size.x),
			"[+-]?[0-9]*\\.?[0-9]*"
		);
		auto ySizeLabel = makeLabel("Size Y", xEditBox->getSize().x + xEditBox->getPosition().x + 10, xLabel->getSize().y);
		auto ySizeEditBox = makeTypeBox(
			yLabel->getSize().x + yLabel->getPosition().x,
			xLabel->getSize().y,
			60,
			xLabel->getSize().y,
			Utils::floatToString(position.size.y),
			"[+-]?[0-9]*\\.?[0-9]*"
		);
		auto angleLabel = makeLabel("Rotation", 0, xLabel->getSize().y * 2);
		auto angleBox = makeTypeBox(
			xLabel->getSize().x,
			xLabel->getSize().y * 2,
			60,
			xLabel->getSize().y,
			Utils::floatToString(position.angle),
			"[+-]?[0-9]*\\.?[0-9]*"
		);

		xEditBox->connect("TextChanged", [&position, xEditBox, collision, collider]{
			if (!xEditBox->getText().isEmpty()) {
				position.position.x = std::stof(xEditBox->getText().toAnsiString());
				if (collision)
					collision->collider->setOrigin(position.position);
				if (collider)
					for (auto &col : collider->colliders)
						col->setOrigin(position.position);
			}
		});
		yEditBox->connect("TextChanged", [&position, yEditBox, collision, collider]{
			if (!yEditBox->getText().isEmpty()) {
				position.position.y = std::stof(yEditBox->getText().toAnsiString());
				if (collision)
					collision->collider->setOrigin(position.position);
				if (collider)
					for (auto &col : collider->colliders)
						col->setOrigin(position.position);
			}
		});
		xSizeEditBox->connect("TextChanged", [&position, xSizeEditBox]{
			if (!xSizeEditBox->getText().isEmpty())
				position.size.x = std::stof(xSizeEditBox->getText().toAnsiString());
		});
		ySizeEditBox->connect("TextChanged", [&position, ySizeEditBox]{
			if (!ySizeEditBox->getText().isEmpty())
				position.size.y = std::stof(ySizeEditBox->getText().toAnsiString());
		});
		angleBox->connect("TextChanged", [&position, angleBox]{
			if (!angleBox->getText().isEmpty())
				position.angle = std::stof(angleBox->getText().toAnsiString());
		});
		panel->setRenderer(render);
		panel->add(xLabel);
		panel->add(xEditBox);
		panel->add(yLabel);
		panel->add(yEditBox);
		panel->add(xSizeLabel);
		panel->add(xSizeEditBox);
		panel->add(ySizeLabel);
		panel->add(ySizeEditBox);
		panel->add(angleLabel);
		panel->add(angleBox);
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::ControllableGui(ECS::Component &component)
	{
		auto &controllable = component.to<ECS::Components::ControllableComponent>();
		auto panel = tgui::Panel::create({300, 30});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto speedLabel = makeLabel("Normal speed", 0, 0);
		auto speedEditBox = makeTypeBox(
			speedLabel->getSize().x,
			0,
			40,
			speedLabel->getSize().y,
			Utils::floatToString(controllable.regularSpeed),
			"[+-]?[0-9]*\\.?[0-9]*"
		);
		auto sprintLabel = makeLabel("Sprint speed", speedEditBox->getSize().x + speedEditBox->getPosition().x + 10, 0);
		auto sprintEditBox = makeTypeBox(
			sprintLabel->getSize().x + sprintLabel->getPosition().x,
			0,
			40,
			speedLabel->getSize().y,
			Utils::floatToString(controllable.sprintSpeed),
			"[+-]?[0-9]*\\.?[0-9]*"
		);

		speedEditBox->connect("TextChanged", [&controllable, speedEditBox]{
			if (!speedEditBox->getText().isEmpty())
				controllable.regularSpeed = std::stof(speedEditBox->getText().toAnsiString());
		});
		sprintEditBox->connect("TextChanged", [&controllable, sprintEditBox]{
			if (!sprintEditBox->getText().isEmpty())
				controllable.sprintSpeed = std::stof(sprintEditBox->getText().toAnsiString());
		});
		panel->setRenderer(render);
		panel->add(speedLabel);
		panel->add(speedEditBox);
		panel->add(sprintLabel);
		panel->add(sprintEditBox);
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::DisplayableGui(ECS::Component &component)
	{
		auto &displayable = component.to<ECS::Components::DisplayableComponent>();
		auto panel = tgui::Panel::create({300, 30});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto speedLabel = makeLabel("Entity config path", 0, 0);
		auto speedEditBox = makeTypeBox(
			speedLabel->getSize().x,
			0,
			160,
			speedLabel->getSize().y,
			displayable._configPath
		);

		speedEditBox->connect("TextChanged", [&displayable, speedEditBox]{
			displayable.setConfigs(speedEditBox->getText().toAnsiString());
		});
		panel->setRenderer(render);
		panel->add(speedLabel);
		panel->add(speedEditBox);
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::ManaGui(ECS::Component &component)
	{
		auto &manaComp = component.to<ECS::Components::ManaComponent>();
		auto panel = tgui::Panel::create({300, 30});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto maxManaLabel = makeLabel("Max mana", 0, 0);
		auto maxManaEditBox = makeTypeBox(
			maxManaLabel->getSize().x,
			0,
			60,
			maxManaLabel->getSize().y,
			Utils::floatToString(manaComp.maxMana),
			"[+-]?[0-9]*\\.?[0-9]*"
		);
		auto manaLabel = makeLabel("Current mana", maxManaEditBox->getSize().x + maxManaEditBox->getPosition().x + 10, 0);
		auto manaEditBox = makeTypeBox(
			manaLabel->getSize().x + manaLabel->getPosition().x,
			0,
			60,
			maxManaLabel->getSize().y,
			Utils::floatToString(manaComp.mana),
			"[+-]?[0-9]*\\.?[0-9]*"
		);

		maxManaEditBox->connect("TextChanged", [&manaComp, maxManaEditBox]{
			if (!maxManaEditBox->getText().isEmpty())
				manaComp.maxMana = std::stof(maxManaEditBox->getText().toAnsiString());
		});
		manaEditBox->connect("TextChanged", [&manaComp, manaEditBox]{
			if (!manaEditBox->getText().isEmpty())
				manaComp.mana = std::stof(manaEditBox->getText().toAnsiString());
		});
		panel->setRenderer(render);
		panel->add(maxManaLabel);
		panel->add(maxManaEditBox);
		panel->add(manaLabel);
		panel->add(manaEditBox);
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::HealthGui(ECS::Component &component)
	{
		auto &healthComp = component.to<ECS::Components::HealthComponent>();
		auto panel = tgui::Panel::create({300, 30});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto maxHealthLabel = makeLabel("Max health", 0, 0);
		auto maxHealthEditBox = makeTypeBox(
			maxHealthLabel->getSize().x,
			0,
			60,
			maxHealthLabel->getSize().y,
			Utils::floatToString(healthComp.maxHealth),
			"[+-]?[0-9]*\\.?[0-9]*"
		);
		auto healthLabel = makeLabel("Current health", maxHealthEditBox->getSize().x + maxHealthEditBox->getPosition().x + 10, 0);
		auto healthEditBox = makeTypeBox(
			healthLabel->getSize().x + healthLabel->getPosition().x,
			0,
			60,
			maxHealthLabel->getSize().y,
			Utils::floatToString(healthComp.health),
			"[+-]?[0-9]*\\.?[0-9]*"
		);

		maxHealthEditBox->connect("TextChanged", [&healthComp, maxHealthEditBox]{
			if (!maxHealthEditBox->getText().isEmpty())
				healthComp.maxHealth = std::stof(maxHealthEditBox->getText().toAnsiString());
		});
		healthEditBox->connect("TextChanged", [&healthComp, healthEditBox]{
			if (!healthEditBox->getText().isEmpty())
				healthComp.health = std::stof(healthEditBox->getText().toAnsiString());
		});
		panel->setRenderer(render);
		panel->add(maxHealthLabel);
		panel->add(maxHealthEditBox);
		panel->add(healthLabel);
		panel->add(healthEditBox);
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::NameGui(ECS::Component &component)
	{
		auto &name = component.to<ECS::Components::NameComponent>();
		auto panel = tgui::Panel::create({300, 30});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto nameLabel = makeLabel("Entity name", 0, 0);
		auto nameEditBox = makeTypeBox(
			nameLabel->getSize().x,
			0,
			160,
			nameLabel->getSize().y,
			name.name
		);

		nameEditBox->connect("TextChanged", [&name, nameEditBox]{
			name.name = nameEditBox->getText().toAnsiString();
		});
		panel->setRenderer(render);
		panel->add(nameLabel);
		panel->add(nameEditBox);
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::DialogGui(ECS::Component &component)
	{
		auto &dialog = component.to<ECS::Components::DialogComponent>();
		auto panel = tgui::ScrollablePanel::create({300, 70});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto speedLabel = makeLabel("Dialog path", 0, 0);
		auto speedEditBox = makeTypeBox(
			speedLabel->getSize().x,
			0,
			160,
			speedLabel->getSize().y,
			dialog.getDialogPath()
		);
		auto errorLabel = makeLabel("", 0, speedLabel->getSize().y);

		try {
			dialog.setDialogPath(dialog.getDialogPath());
			errorLabel->setText("");
		} catch (std::exception &e) {
			errorLabel->setText(getLastExceptionName() + "\n" + e.what());
		}
		errorLabel->getRenderer()->setTextColor("red");
		speedEditBox->connect("TextChanged", [&dialog, speedEditBox, errorLabel]{
			try {
				dialog.setDialogPath(speedEditBox->getText());
				errorLabel->setText("");
			} catch (std::exception &e) {
				errorLabel->setText(getLastExceptionName() + "\n" + e.what());
			}
		});
		panel->setRenderer(render);
		panel->add(speedLabel);
		panel->add(speedEditBox);
		panel->add(errorLabel);
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::EmptyGui()
	{
		return tgui::Panel::create({0, 0});
	}

	tgui::Panel::Ptr ComponentGui::InventoryGui(Game &game, ECS::Component &component)
	{
		auto &inventory = component.to<ECS::Components::InventoryComponent>();
		auto panel = tgui::Panel::create({300, 50});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto sizeLabel = makeLabel("Inventory size", 0, 0);
		auto itemsLabel = makeLabel("Inventory items", 0, sizeLabel->getSize().y);
		auto sizeEditBox = makeTypeBox(
			itemsLabel->getSize().x,
			0,
			60,
			sizeLabel->getSize().y,
			std::to_string(inventory.maxSize),
			"[+-]?[0-9]+"
		);
		std::string itemsStr;

		for (auto &item : inventory.items)
			itemsStr += std::to_string(item->getIndex()) + ",";

		auto itemsEditBox = makeTypeBox(
			itemsLabel->getSize().x,
			sizeLabel->getSize().y,
			160,
			sizeLabel->getSize().y,
			itemsStr,
			"(([0-9]+,)*[0-9]+)?"
		);

		sizeEditBox->connect("TextChanged", [&inventory, sizeEditBox]{
			inventory.maxSize = std::stol(sizeEditBox->getText().toAnsiString());
		});
		itemsEditBox->connect("TextChanged", [&inventory, &game, itemsEditBox]{
			std::stringstream stream(itemsEditBox->getText());
			std::string token;

			inventory.items.clear();
			while (std::getline(stream, token, ',')) {
				try {
					inventory.items.push_back(game.resources.items.at(std::stol(token)));
				} catch (std::out_of_range &) {}
			}
		});
		panel->setRenderer(render);
		panel->add(sizeLabel);
		panel->add(sizeEditBox);
		panel->add(itemsLabel);
		panel->add(itemsEditBox);
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::CutsceneGui(ECS::Component &component)
	{
		auto &cutscene = component.to<ECS::Components::CutsceneComponent>();
		auto panel = tgui::ScrollablePanel::create({300, 70});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto speedLabel = makeLabel("Module path", 0, 0);
		auto speedEditBox = makeTypeBox(
			speedLabel->getSize().x,
			0,
			160,
			speedLabel->getSize().y,
			cutscene.getModulePath()
		);
		auto errorLabel = makeLabel("", 0, speedLabel->getSize().y);

		try {
			cutscene.setModulePath(cutscene.getModulePath());
			errorLabel->setText("");
		} catch (std::exception &e) {
			errorLabel->setText(getLastExceptionName() + "\n" + e.what());
		}
		errorLabel->getRenderer()->setTextColor("red");
		speedEditBox->connect("TextChanged", [&cutscene, speedEditBox, errorLabel]{
			try {
				cutscene.setModulePath(speedEditBox->getText());
				errorLabel->setText("");
			} catch (std::exception &e) {
				errorLabel->setText(getLastExceptionName() + "\n" + e.what());
			}
		});
		panel->setRenderer(render);
		panel->add(speedLabel);
		panel->add(speedEditBox);
		panel->add(errorLabel);
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::AIGui(ECS::Component &component)
	{
		auto &ai = component.to<ECS::Components::AIComponent>();
		auto panel = tgui::ScrollablePanel::create({300, 70});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto speedLabel = makeLabel("Module path", 0, 0);
		auto speedEditBox = makeTypeBox(
			speedLabel->getSize().x,
			0,
			160,
			speedLabel->getSize().y,
			ai.ai.getModulePath()
		);
		auto errorLabel = makeLabel("", 0, speedLabel->getSize().y);

		try {
			ai.ai.changeModule(ai.ai.getModulePath());
			errorLabel->setText("");
		} catch (std::exception &e) {
			errorLabel->setText(getLastExceptionName() + "\n" + e.what());
		}
		errorLabel->getRenderer()->setTextColor("red");
		speedEditBox->connect("TextChanged", [&ai, speedEditBox, errorLabel]{
			try {
				ai.ai.changeModule(speedEditBox->getText());
				errorLabel->setText("");
			} catch (std::exception &e) {
				errorLabel->setText(getLastExceptionName() + "\n" + e.what());
			}
		});
		panel->setRenderer(render);
		panel->add(speedLabel);
		panel->add(speedEditBox);
		panel->add(errorLabel);
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::ShootGui(ECS::Component &component)
	{
		auto &shoot = component.to<ECS::Components::ShootComponent>();
		auto panel = tgui::ScrollablePanel::create({300, 70});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto speedLabel = makeLabel("Module path", 0, 0);
		auto speedEditBox = makeTypeBox(
			speedLabel->getSize().x,
			0,
			160,
			speedLabel->getSize().y,
			shoot.getHandlerPath()
		);
		auto errorLabel = makeLabel("", 0, speedLabel->getSize().y);

		try {
			shoot.setHandlerPath(shoot.getHandlerPath());
			errorLabel->setText("");
		} catch (std::exception &e) {
			errorLabel->setText(getLastExceptionName() + "\n" + e.what());
		}
		errorLabel->getRenderer()->setTextColor("red");
		speedEditBox->connect("TextChanged", [&shoot, speedEditBox, errorLabel]{
			try {
				shoot.setHandlerPath(speedEditBox->getText());
				errorLabel->setText("");
			} catch (std::exception &e) {
				errorLabel->setText(getLastExceptionName() + "\n" + e.what());
			}
		});
		panel->setRenderer(render);
		panel->add(speedLabel);
		panel->add(speedEditBox);
		panel->add(errorLabel);
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::DeckGui(ECS::Component &component)
	{
		auto &deck = component.to<ECS::Components::DeckComponent>();
		auto panel = tgui::ScrollablePanel::create({300, 70});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto speedLabel = makeLabel("Tree path", 0, 0);
		auto speedEditBox = makeTypeBox(
			speedLabel->getSize().x,
			0,
			160,
			speedLabel->getSize().y,
			deck.getTreePath()
		);
		auto errorLabel = makeLabel("", 0, speedLabel->getSize().y);

		try {
			deck.setTreePath(deck.getTreePath());
			errorLabel->setText("");
		} catch (std::exception &e) {
			errorLabel->setText(getLastExceptionName() + "\n" + e.what());
		}
		errorLabel->getRenderer()->setTextColor("red");
		speedEditBox->connect("TextChanged", [&deck, speedEditBox, errorLabel]{
			try {
				deck.setTreePath(speedEditBox->getText());
				errorLabel->setText("");
			} catch (std::exception &e) {
				errorLabel->setText(getLastExceptionName() + "\n" + e.what());
			}
		});
		panel->setRenderer(render);
		panel->add(speedLabel);
		panel->add(speedEditBox);
		panel->add(errorLabel);
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::ExperienceGui(ECS::Component &component)
	{
		auto &xpComp = component.to<ECS::Components::ExperienceComponent>();
		auto panel = tgui::Panel::create({300, 30});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto currentLevelLabel = makeLabel("Level", 0, 0);
		auto currentLevelEditBox = makeTypeBox(
			currentLevelLabel->getSize().x,
			0,
			60,
			currentLevelLabel->getSize().y,
			std::to_string(xpComp.level),
			"[0-9]+"
		);
		auto xpLabel = makeLabel("Experience", currentLevelEditBox->getSize().x + currentLevelEditBox->getPosition().x + 10, 0);
		auto xpEditBox = makeTypeBox(
			xpLabel->getSize().x + xpLabel->getPosition().x,
			0,
			60,
			currentLevelLabel->getSize().y,
			std::to_string(xpComp.exp),
			"[0-9]+"
		);

		currentLevelEditBox->connect("TextChanged", [&xpComp, currentLevelEditBox]{
			if (!currentLevelEditBox->getText().isEmpty())
				xpComp.level = std::stol(currentLevelEditBox->getText().toAnsiString());
		});
		xpEditBox->connect("TextChanged", [&xpComp, xpEditBox]{
			if (!xpEditBox->getText().isEmpty())
				xpComp.exp = std::stol(xpEditBox->getText().toAnsiString());
		});
		panel->setRenderer(render);
		panel->add(currentLevelLabel);
		panel->add(currentLevelEditBox);
		panel->add(xpLabel);
		panel->add(xpEditBox);
		return panel;
	}

	tgui::Panel::Ptr ComponentGui::build(Game &game, ECS::Entity &entity, TouhouFanGame::ECS::Component &component)
	{
		try {
			return _builders.at(component.getName())(game, entity, component);
		} catch (std::out_of_range &) {
			return EmptyGui();
		}
	}
}