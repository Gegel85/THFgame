//
// Created by Gegel85 on 29/12/2019.
//

#include "ComponentGui.hpp"
#include "GuiUtils.hpp"
#include "../Core/ECS/Components/MovableComponent.hpp"
#include "../Core/ECS/Components/PositionComponent.hpp"
#include "../Core/Utils.hpp"
#include "../Core/ECS/Components/ControllableComponent.hpp"
#include "../Core/ECS/Components/DisplayableComponent.hpp"
#include "../Core/ECS/Components/BlockedByTerrainComponent.hpp"
#include "../Core/ECS/Components/ManaComponent.hpp"
#include "../Core/ECS/Components/HealthComponent.hpp"
#include "../Core/ECS/Components/NameComponent.hpp"
#include "../Core/ECS/Components/InventoryComponent.hpp"
#include "../Core/ECS/Components/DialogComponent.hpp"

namespace TouhouFanGame
{
	std::map<std::string, std::function<tgui::Panel::Ptr(Game &, ECS::Component &component)>> ComponentGui::_builders{
		{"Movable",          [](Game &game, ECS::Component &component){ return MovableGui(game, component);      }},
		{"Position",         [](Game &game, ECS::Component &component){ return PositionGui(game, component);     }},
		{"Controllable",     [](Game &game, ECS::Component &component){ return ControllableGui(game, component); }},
		{"Displayable",      [](Game &game, ECS::Component &component){ return DisplayableGui(game, component);  }},
		{"Mana",             [](Game &game, ECS::Component &component){ return ManaGui(game, component);         }},
		{"Health",           [](Game &game, ECS::Component &component){ return HealthGui(game, component);       }},
		{"Name",             [](Game &game, ECS::Component &component){ return NameGui(game, component);         }},
		{"Inventory",        [](Game &game, ECS::Component &component){ return InventoryGui(game, component);    }},
		{"Dialog",           [](Game &game, ECS::Component &component){ return DialogGui(game, component);       }},
	};
	
	tgui::Panel::Ptr ComponentGui::MovableGui(Game &, ECS::Component &component)
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
			std::to_string(movable.dir),
			R"(0|[1-9]\d{0,1}|[1-2]\d{2}|2[0-4]\d|25[0-5])"
		);

		speedEditBox->connect("TextChanged", [&movable, speedEditBox]{
			if (!speedEditBox->getText().isEmpty())
				movable.speed = std::stof(speedEditBox->getText().toAnsiString());
		});
		dirEditBox->connect("TextChanged", [&movable, dirEditBox]{
			movable.dir = std::stol(dirEditBox->getText().toAnsiString());
		});
		panel->setRenderer(render);
		panel->add(speedLabel);
		panel->add(speedEditBox);
		panel->add(dirLabel);
		panel->add(dirEditBox);
		return panel;
	}
	
	tgui::Panel::Ptr ComponentGui::PositionGui(Game &, ECS::Component &component)
	{
		auto &position = component.to<ECS::Components::PositionComponent>();
		auto panel = tgui::Panel::create({300, 50});
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

		xEditBox->connect("TextChanged", [&position, xEditBox]{
			if (!xEditBox->getText().isEmpty())
				position.position.x = std::stof(xEditBox->getText().toAnsiString());
		});
		yEditBox->connect("TextChanged", [&position, yEditBox]{
			if (!yEditBox->getText().isEmpty())
				position.position.y = std::stof(yEditBox->getText().toAnsiString());
		});
		xSizeEditBox->connect("TextChanged", [&position, xSizeEditBox]{
			if (!xSizeEditBox->getText().isEmpty())
				position.size.x = std::stof(xSizeEditBox->getText().toAnsiString());
		});
		ySizeEditBox->connect("TextChanged", [&position, ySizeEditBox]{
			if (!ySizeEditBox->getText().isEmpty())
				position.size.y = std::stof(ySizeEditBox->getText().toAnsiString());
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
		return panel;
	}
	
	tgui::Panel::Ptr ComponentGui::ControllableGui(Game &, ECS::Component &component)
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
	
	tgui::Panel::Ptr ComponentGui::DisplayableGui(Game &, ECS::Component &component)
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
			displayable._configPath = speedEditBox->getText().toAnsiString();
		});
		panel->setRenderer(render);
		panel->add(speedLabel);
		panel->add(speedEditBox);
		return panel;
	}
	
	tgui::Panel::Ptr ComponentGui::ManaGui(Game &, ECS::Component &component)
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

	tgui::Panel::Ptr ComponentGui::HealthGui(Game &, ECS::Component &component)
	{
		auto &healthComp = component.to<ECS::Components::HealthComponent>();
		auto panel = tgui::Panel::create({300, 30});
		auto render = tgui::RendererData::create({
			{"backgroundcolor", "transparent"}
		});
		auto maxHealthLabel = makeLabel("Max mana", 0, 0);
		auto maxHealthEditBox = makeTypeBox(
			maxHealthLabel->getSize().x,
			0,
			60,
			maxHealthLabel->getSize().y,
			Utils::floatToString(healthComp.maxHealth),
			"[+-]?[0-9]*\\.?[0-9]*"
		);
		auto healthLabel = makeLabel("Current mana", maxHealthEditBox->getSize().x + maxHealthEditBox->getPosition().x + 10, 0);
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

	tgui::Panel::Ptr ComponentGui::NameGui(Game &, ECS::Component &component)
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

	tgui::Panel::Ptr ComponentGui::DialogGui(TouhouFanGame::Game &, TouhouFanGame::ECS::Component &component)
	{
		auto &dialog = component.to<ECS::Components::DialogComponent>();
		auto panel = tgui::Panel::create({300, 70});
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

	tgui::Panel::Ptr ComponentGui::EmptyGui(Game &, ECS::Component &)
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
	
	tgui::Panel::Ptr ComponentGui::build(Game &game, TouhouFanGame::ECS::Component &component)
	{
		try {
			return _builders.at(component.getName())(game, component);
		} catch (std::out_of_range &) {
			return EmptyGui(game, component);
		}
	}
}