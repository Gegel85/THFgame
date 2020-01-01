//
// Created by Gegel85 on 23/12/2019.
//

#include <TGUI/TGUI.hpp>
#include "MapEditor.hpp"
#include "../Core/Loader.hpp"
#include "Menus/MainMenu.hpp"
#include "GuiUtils.hpp"
#include "../Core/Utils.hpp"
#include "../Core/ECS/Factories/EntityFactory.hpp"
#include "../Core/ECS/Factories/ComponentFactory.hpp"
#include "ComponentGui.hpp"

namespace TouhouFanGame
{
	MapEditor::MapParams::MapParams(const TouhouFanGame::Map &map) :
		size(map._size),
		solid(map._solidBorders),
		music(map._music),
		tilemap(map._tileMap),
		tilesize(map._tileSize)
	{
		std::memcpy(this->links, map._links, sizeof(this->links));
	}

	MapEditor::MapEditor() :
		_map(this->_game)
	{
	}

	MapEditor::~MapEditor()
	{
		Loader::saveSettings(this->_game.state.settings);
	}

	void MapEditor::_displaySettings()
	{
		auto win = openWindowWithFocus(*this->_gui);

		win->setTitle("Settings");
		win->setSize(400, 400);
		win->loadWidgetsFromFile("assets/gui/Settings.txt");
		win->setFocused(true);

		auto slider = win->get<tgui::Slider>("VolumeSlider");

		slider->setMinimum(0);
		slider->setMaximum(100);
		slider->setValue(this->_game.state.settings.musicVolume);
		slider->connect("ValueChanged", [this, slider]() {
			this->_game.state.settings.musicVolume = slider->getValue();
			this->_game.resources.setMusicVolume(this->_game.state.settings.musicVolume);
		});
	}

	void MapEditor::_showMapEditWindow()
	{
		this->_params = this->_map;

		auto win = openWindowWithFocus(*this->_gui, [this]{
			this->_game.resources.playMusic(this->_map._music);
		});

		win->setTitle("Change map settings");
		win->setSize(400, 200);
		win->loadWidgetsFromFile("assets/gui/EditMap.txt");
		win->setFocused(true);

		auto width = win->get<tgui::EditBox>("MapWidth");
		auto height = win->get<tgui::EditBox>("MapHeight");
		auto tsize = win->get<tgui::EditBox>("TileSize");
		auto border = win->get<tgui::CheckBox>("SolidBorder");
		auto tmap = win->get<tgui::ComboBox>("TileMap");
		auto music = win->get<tgui::ComboBox>("Music");
		auto buttonLoad = win->get<tgui::Button>("BtnLoad");
		auto buttonCancelLoadingImage = win->get<tgui::Button>("BtnCancel");
		auto upLink = win->get<tgui::EditBox>("UpLink");
		auto downLink = win->get<tgui::EditBox>("DownLink");
		auto leftLink = win->get<tgui::EditBox>("LeftLink");
		auto rightLink = win->get<tgui::EditBox>("RightLink");

		width->setText(std::to_string(this->_params.size.x));
		width->connect("TextChanged", [this, width]{
			try {
				this->_params.size.x = std::stol(static_cast<std::string>(width->getText()));
			} catch (std::invalid_argument &) {
				this->_params.size.x = 1;
			}
		});

		height->setText(std::to_string(this->_params.size.y));
		height->connect("TextChanged", [this, height]{
			try {
				this->_params.size.y = std::stol(static_cast<std::string>(height->getText()));
			} catch (std::invalid_argument &) {
				this->_params.size.y = 1;
			}
		});

		tsize->setText(std::to_string(this->_params.tilesize));
		tsize->connect("TextChanged", [this, tsize]{
			try {
				this->_params.tilesize = std::stol(static_cast<std::string>(tsize->getText()));
			} catch (std::invalid_argument &) {
				this->_params.tilesize = 1;
			}
		});

		upLink->setText(std::to_string(this->_params.links[Input::UP]));
		upLink->connect("TextChanged", [this, upLink]{
			this->_params.links[Input::UP] = std::stol(upLink->getText().toAnsiString());
		});

		downLink->setText(std::to_string(this->_params.links[Input::DOWN]));
		downLink->connect("TextChanged", [this, downLink]{
			this->_params.links[Input::DOWN] = std::stol(downLink->getText().toAnsiString());
		});

		leftLink->setText(std::to_string(this->_params.links[Input::LEFT]));
		leftLink->connect("TextChanged", [this, leftLink]{
			this->_params.links[Input::LEFT] = std::stol(leftLink->getText().toAnsiString());
		});

		rightLink->setText(std::to_string(this->_params.links[Input::RIGHT]));
		rightLink->connect("TextChanged", [this, rightLink]{
			this->_params.links[Input::RIGHT] = std::stol(rightLink->getText().toAnsiString());
		});

		tmap->removeAllItems();
		for (auto &texture : this->_game.resources.textures)
			tmap->addItem(texture.first);
		tmap->setSelectedItem(this->_params.tilemap);

		tmap->connect("ItemSelected", [this, tmap]{
			this->_params.tilemap = tmap->getSelectedItem();
		});

		music->removeAllItems();
		for (auto &m : this->_game.resources.musics)
			music->addItem(m.first);
		music->setSelectedItem(this->_params.music);

		music->connect("ItemSelected", [this, music]{
			this->_params.music = music->getSelectedItem();
			this->_game.resources.playMusic(this->_params.music);
		});

		border->setChecked(this->_params.solid);
		border->connect("Changed", [this, border]{
			this->_params.solid = border->isChecked();
		});

		buttonCancelLoadingImage->connect("pressed", [win]{
			win->close();
		});

		buttonLoad->connect("pressed", [this, win]{
			std::vector<unsigned char> temp(this->_params.size.x * this->_params.size.y);

			for (unsigned x = 0; x < this->_params.size.x; x++)
				for (unsigned y = 0; y < this->_params.size.y; y++)
					temp[x + y * this->_params.size.x] = this->_map.getObjectAt(x * this->_map._tileSize, y * this->_map._tileSize);
			this->_map._objects = temp;
			this->_map._size = this->_params.size;
			this->_map._music = this->_params.music;
			this->_map._tileMap = this->_params.tilemap;
			this->_map._tileSize = this->_params.tilesize;
			this->_map._solidBorders = this->_params.solid;
			std::memcpy(this->_map._links, this->_params.links, sizeof(this->_params.links));
			win->close();
		});
	}

	void MapEditor::_makeAllWidgets()
	{
		this->_gui->loadWidgetsFromFile("assets/gui/MapEditor.txt");

		auto menuBar = this->_gui->get<tgui::MenuBar>("main_bar");
		menuBar->connect("MouseEntered", [](tgui::Widget::Ptr bar, const std::string&){
			bar->moveToFront();
		});
		menuBar->connectMenuItem({"File", "New map"}, [this, menuBar]{
			this->_resetMap();
			menuBar->setMenuItemEnabled({"File", "Save"}, false);
			this->_game.resources.playMusic(this->_map._music);
		});
		menuBar->connectMenuItem({"File", "Load map"}, [this, menuBar]{
			showLoadFileWindow(*this->_gui, "Load map", "Open", 0, [this, menuBar](unsigned short id) {
				try {
					this->_map.loadFromFile("assets/maps/map_" + std::to_string(id) + ".map");
					this->_loaded = id;
					menuBar->setMenuItemEnabled({"File", "Save"}, true);
				} catch (std::exception &e) {
					logger.error(getLastExceptionName() + ": " + e.what());
					Utils::dispMsg(
						"assets/maps/map_" + std::to_string(id) + ".map",
						"Couldn't load file assets/maps/map_" + std::to_string(id) + ".map\n\n" +
						getLastExceptionName() + ":\n" + e.what(),
						MB_ICONERROR
					);
				}
			});
		});
		menuBar->connectMenuItem({"File", "Save"}, [this]{
			try {
				this->_map.saveMapToFile("assets/maps/map_" + std::to_string(this->_loaded) + ".map");
			} catch (std::exception &e) {
				logger.error(getLastExceptionName() + ": " + e.what());
				Utils::dispMsg(
					"assets/maps/map_" + std::to_string(this->_loaded) + ".map",
					"Couldn't save file assets/maps/map_" + std::to_string(this->_loaded) + ".map\n\n" +
					getLastExceptionName() + ":\n" + e.what(),
					MB_ICONERROR
				);
			}
		});
		menuBar->connectMenuItem({"File", "Save as"}, [this, menuBar]{
			showLoadFileWindow(*this->_gui, "Save map", "Save", 0, [this, menuBar](unsigned short id) {
				try {
					this->_map.saveMapToFile("assets/maps/map_" + std::to_string(id) + ".map");
					this->_loaded = id;
					menuBar->setMenuItemEnabled({"File", "Save"}, true);
				} catch (std::exception &e) {
					logger.error(getLastExceptionName() + ": " + e.what());
					Utils::dispMsg(
						"assets/maps/map_" + std::to_string(id) + ".map",
						"Couldn't save file assets/maps/map_" + std::to_string(id) + ".map\n\n" +
						getLastExceptionName() + ":\n" + e.what(),
						MB_ICONERROR
					);
				}
			});
		});
		menuBar->connectMenuItem({"File", "Map properties"}, [this]{
			this->_showMapEditWindow();
		});
		menuBar->connectMenuItem({"File", "Settings"}, [this]{
			this->_displaySettings();
		});
		menuBar->connectMenuItem({"File", "Quit"}, [this]{
			this->_game.resources.screen->close();
		});
		menuBar->connectMenuItem({"Windows", "Tools"}, [this]{
			this->_showToolBox();
		});
		menuBar->connectMenuItem({"New", "Entity"}, [this]{
			this->_showNewEntityBox();
		});
		menuBar->connectMenuItem({"New", "Teleporter"}, [this]{
			this->_showNewTeleporterBox();
		});
	}

	void MapEditor::_showNewEntityBox()
	{
		auto window = openWindowWithFocus(*this->_gui);

		window->loadWidgetsFromFile("assets/gui/windows/newEntity.txt");

		auto box = window->get<tgui::ComboBox>("EntityName");
		auto okButton = window->get<tgui::Button>("OKButton");
		auto cancelButton = window->get<tgui::Button>("CancelButton");

		window->setTitle("New entity");
		window->setSize({140, 70});
		box->removeAllItems();
		for (auto &val : ECS::Factory::EntityFactory::getItemList())
			box->addItem(val);
		box->setSelectedItem("Entity");
		okButton->connect("Pressed", [this, box, window]{
			this->_showEntityProperties(
				this->_map._core.makeEntity(box->getSelectedItem())
			);
			window->close();
		});
		cancelButton->connect("Pressed", [window]{
			window->close();
		});
	}

	void MapEditor::_removeComponentFromEntity(TouhouFanGame::ECS::Entity &entity, const std::string &name)
	{
		entity.removeComponent(name);
		for (const auto &comp : entity.getComponentsNames()) {
			const auto &deps = this->_map._core.getSystemByName(comp).getDependencies();

			if (std::find(deps.begin(), deps.end(), name) != deps.end())
				this->_removeComponentFromEntity(entity, comp);
		}
	}

	void MapEditor::_showEntityProperties(TouhouFanGame::ECS::Entity &entity)
	{
		auto window = openWindowWithFocus(*this->_gui);

		window->loadWidgetsFromFile("assets/gui/windows/entity.txt");

		auto panel = window->get<tgui::ScrollablePanel>("ScrollablePanel1");
		auto name = panel->get<tgui::Label>("EntityName");
		auto componentBox = panel->get<tgui::ComboBox>("ComponentName");
		auto deleteButton = panel->get<tgui::Button>("Delete");
		auto newButton = panel->get<tgui::Button>("New");
		auto okButton = panel->get<tgui::Button>("okButton");
		const auto basePos = name->getSize().y + name->getPosition().y;
		unsigned pos = 0;

		name->setText(entity.getName());
		window->setSize({350, 250});
		panel->setSize({350, 250});
		window->setTitle("Entity " + std::to_string(entity.getID()));

		for (auto &componentName : entity.getComponentsNames()) {
			auto pan = ComponentGui::build(this->_game, entity.getComponent(componentName));
			auto label = makeLabel(componentName, 10, basePos + pos);
			auto button = tgui::Button::create("X");

			button->setPosition("parent.w - 40", basePos + pos);
			button->setSize({20, 20});
			button->connect("Pressed", [window, this, componentName, &entity]{
				this->_removeComponentFromEntity(entity, componentName);
				window->close();
				this->_showEntityProperties(entity);
			});
			pan->setPosition(10, basePos + pos + label->getSize().y);
			panel->add(label, componentName + "Label");
			panel->add(pan, componentName + "Component");
			panel->add(button);
			pos += pan->getSize().y + label->getSize().y;
		}

		componentBox->setPosition(
			componentBox->getPosition().x,
			componentBox->getPosition().y + pos
		);
		componentBox->removeAllItems();
		for (auto &val : ECS::Factory::ComponentFactory::getItemList())
			if (!entity.hasComponent(val)) {
				componentBox->addItem(val);
				componentBox->setSelectedItem(val);
			}
		if (componentBox->getItemCount() == 0)
			newButton->setEnabled(false);

		okButton->setPosition(
			okButton->getPosition().x,
			okButton->getPosition().y + pos
		);
		okButton->connect("Pressed", [window]{
			window->close();
		});

		newButton->setPosition(
			newButton->getPosition().x,
			newButton->getPosition().y + pos
		);
		newButton->connect("Pressed", [window, &entity, componentBox, this]{
			entity.addComponent(ECS::Factory::ComponentFactory::build(this->_game, componentBox->getSelectedItem()));
			for (const auto &dep : this->_map._core.getSystemByName(componentBox->getSelectedItem()).getDependencies())
				entity.addComponent(ECS::Factory::ComponentFactory::build(this->_game, dep));
			window->close();
			this->_showEntityProperties(entity);
		});

		deleteButton->setPosition(
			deleteButton->getPosition().x,
			deleteButton->getPosition().y + pos
		);
		deleteButton->connect("Pressed", [window, &entity, this]{
			this->_map._core.deleteEntity(entity);
			window->close();
		});
	}

	void MapEditor::_showNewTeleporterBox()
	{
		auto window = openWindowWithFocus(*this->_gui);

		window->setTitle("New teleporter");
	}

	void MapEditor::_showToolBox()
	{
		auto window = this->_gui->get<tgui::ChildWindow>("ToolWindow");

		if (!window) {
			window = tgui::ChildWindow::create();
			this->_gui->add(window, "ToolWindow");
		}
		window->setTitle("Tools");
		window->setPosition(32, 32);
		window->setSize({110, 160});
		window->loadWidgetsFromFile("assets/gui/windows/tools.txt");
	}

	void MapEditor::_renderMap()
	{
		this->_map._cameraCenter = {
			this->_game.resources.screen->getSize().x / 2.f - this->_cameraPos.x,
			this->_game.resources.screen->getSize().y / 2.f - this->_cameraPos.y
		};
		this->_map._cameraUpdated = true;

		auto &system = this->_map._core.getSystemByName("Displayable");

		for (auto &entity : this->_map._core.getEntityByComponent("Displayable"))
			system.updateEntity(entity);
		this->_map.render();
	}

	void MapEditor::_resetMap()
	{
		this->_map.reset();
		this->_map._tileMap = this->_game.resources.textures.begin()->first;
		this->_map._tileSize = 16;
		this->_map._music = this->_game.resources.musics.begin()->first;
		this->_map._size = {32, 32};
		this->_map._objects.resize(32 * 32);
		this->_cameraPos = {0, 20};
	}

	void MapEditor::setup()
	{
		logger.info("Setting up...");
		logger.debug("Opening main window");
		this->_game.resources.screen = std::make_unique<Rendering::Screen>(this->_game.resources, "THFgame map editor", 800, 640);
		this->_gui = std::make_unique<tgui::Gui>(*this->_game.resources.screen);
		this->_game.state.menuMgr.addMenu<MainMenu>("main_menu", this->_map, *this->_gui, *this->_game.resources.screen);

		this->_makeAllWidgets();
		this->_font.loadFromFile("assets/arial.ttf");
		this->_game.resources.screen->setFont(this->_font);

		logger.info("Loading assets...");
		Loader::loadAssets(this->_game);

		this->_resetMap();
	}

	int MapEditor::run()
	{
		if (!this->_game.resources.screen)
			return EXIT_FAILURE;

		sf::Event event;

		logger.info("Starting editor.");
		this->_game.resources.playMusic(this->_map._music);
		this->_game.state.menuMgr.changeMenu("main_menu");
		while (this->_game.resources.screen->isOpen()) {
			this->_game.resources.screen->clear();

			while (this->_game.resources.screen->pollEvent(event)) {
				if (this->_gui->handleEvent(event))
					continue;
				switch (event.type) {
				case sf::Event::Closed:
					this->_game.resources.screen->close();
					break;
				case sf::Event::Resized:
					this->_game.resources.screen->setView(sf::View{sf::FloatRect(0, 0, event.size.width, event.size.height)});
					this->_gui->setView(sf::View{sf::FloatRect(0, 0, event.size.width, event.size.height)});
					break;
				case sf::Event::MouseButtonPressed:
				default:
					break;
				}
			}

			for (auto e = this->_game.state.settings.input->pollEvent(); e; e = this->_game.state.settings.input->pollEvent())
				this->_game.state.menuMgr.handleEvent(*e);

			this->_renderMap();
			this->_game.state.menuMgr.renderMenu();
			this->_game.resources.screen->display();
		}
		return EXIT_SUCCESS;
	}
}
