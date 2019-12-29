//
// Created by Gegel85 on 29/12/2019.
//

#include "ComponentGui.hpp"
#include "GuiUtils.hpp"
#include "../Core/ECS/Components/MovableComponent.hpp"
#include "../Core/ECS/Components/PositionComponent.hpp"
#include "../Core/Utils.hpp"

namespace TouhouFanGame
{
	std::map<std::string, std::function<tgui::Panel::Ptr(ECS::Component &component)>> ComponentGui::_builders{
		{"Movable",          [](ECS::Component &component){ return MovableGui(component);          }},
		{"Position",         [](ECS::Component &component){ return PositionGui(component);         }},
		{"Controllable",     [](ECS::Component &component){ return ControllableGui(component);     }},
		{"Displayable",      [](ECS::Component &component){ return DisplayableGui(component);      }},
		{"BlockedByTerrain", [](ECS::Component &component){ return BlockedByTerrainGui(component); }},
		{"Mana",             [](ECS::Component &component){ return ManaGui(component);             }},
		{"Health",           [](ECS::Component &component){ return HealthGui(component);           }},
		{"Name",             [](ECS::Component &component){ return NameGui(component);             }},
		{"PlayerHUD",        [](ECS::Component &component){ return PlayerHUDGui(component);        }},
		{"Inventory",        [](ECS::Component &component){ return InventoryGui(component);        }},
	};
	
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
			std::to_string(movable.dir),
			R"(0|[1-9]\d{0,1}|[1-2]\d{2}|2[0-4]\d|25[0-5])"
		);

		speedEditBox->connect("TextChanged", [&movable, speedEditBox]{
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
	
	tgui::Panel::Ptr ComponentGui::PositionGui(ECS::Component &component)
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
			position.position.x = std::stof(xEditBox->getText().toAnsiString());
		});
		yEditBox->connect("TextChanged", [&position, yEditBox]{
			position.position.y = std::stof(yEditBox->getText().toAnsiString());
		});
		xSizeEditBox->connect("TextChanged", [&position, xSizeEditBox]{
			position.size.x = std::stof(xSizeEditBox->getText().toAnsiString());
		});
		ySizeEditBox->connect("TextChanged", [&position, ySizeEditBox]{
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
	
	tgui::Panel::Ptr ComponentGui::ControllableGui(ECS::Component &component)
	{
		
	}
	
	tgui::Panel::Ptr ComponentGui::DisplayableGui(ECS::Component &component)
	{
		
	}
	
	tgui::Panel::Ptr ComponentGui::BlockedByTerrainGui(ECS::Component &component)
	{
		
	}
	
	tgui::Panel::Ptr ComponentGui::ManaGui(ECS::Component &component)
	{
		
	}
	
	tgui::Panel::Ptr ComponentGui::HealthGui(ECS::Component &component)
	{
		
	}
	
	tgui::Panel::Ptr ComponentGui::NameGui(ECS::Component &component)
	{
		
	}
	
	tgui::Panel::Ptr ComponentGui::PlayerHUDGui(ECS::Component &component)
	{
		
	}
	
	tgui::Panel::Ptr ComponentGui::InventoryGui(ECS::Component &component)
	{
		
	}
	
	tgui::Panel::Ptr ComponentGui::build(TouhouFanGame::ECS::Component &component)
	{
		try {
			return _builders[component.getName()](component);
		} catch (std::out_of_range &) {
			return tgui::Panel::create();
		}
	}
}