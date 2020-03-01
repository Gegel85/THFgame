cmake_minimum_required(VERSION 3.10)
project(THFgame)

set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
	if (CMAKE_COMPILER_IS_GNUCC)
		add_compile_options(-Wall -Wextra -W -g -D_DEBUG)
	endif (CMAKE_COMPILER_IS_GNUCC)
endif ()
if ("${CMAKE_BUILD_TYPE}" STREQUAL Release)
	if (CMAKE_COMPILER_IS_GNUCC)
		if (WIN32)
			add_link_options(-mwindows)
		endif (WIN32)
	endif (CMAKE_COMPILER_IS_GNUCC)
endif ()
if (WIN32)
	set(ICON icon.rc)
endif (WIN32)

include_directories(nlohmann)
include_directories(sol)

add_library(
	THFgame-core SHARED
	src/Core/ECS/Component.cpp
	src/Core/ECS/Component.hpp
	src/Core/ECS/Components/BasicSerializeComponent.cpp
	src/Core/ECS/Components/BasicSerializeComponent.hpp
	src/Core/ECS/Components/BlockedByTerrainComponent.cpp
	src/Core/ECS/Components/BlockedByTerrainComponent.hpp
	src/Core/ECS/Components/ControllableComponent.cpp
	src/Core/ECS/Components/ControllableComponent.hpp
	src/Core/ECS/Components/DisplayableComponent.cpp
	src/Core/ECS/Components/DisplayableComponent.hpp
	src/Core/ECS/Components/HealthComponent.cpp
	src/Core/ECS/Components/HealthComponent.hpp
	src/Core/ECS/Components/InventoryComponent.cpp
	src/Core/ECS/Components/InventoryComponent.hpp
	src/Core/ECS/Components/ManaComponent.cpp
	src/Core/ECS/Components/ManaComponent.hpp
	src/Core/ECS/Components/MovableComponent.cpp
	src/Core/ECS/Components/MovableComponent.hpp
	src/Core/ECS/Components/NameComponent.cpp
	src/Core/ECS/Components/NameComponent.hpp
	src/Core/ECS/Components/PlayerHudComponent.cpp
	src/Core/ECS/Components/PlayerHudComponent.hpp
	src/Core/ECS/Components/PositionComponent.cpp
	src/Core/ECS/Components/PositionComponent.hpp
	src/Core/ECS/Core.cpp
	src/Core/ECS/Core.hpp
	src/Core/ECS/Entity.cpp
	src/Core/ECS/Entity.hpp
	src/Core/ECS/Exceptions.hpp
	src/Core/ECS/Factories/ComponentFactory.cpp
	src/Core/ECS/Factories/ComponentFactory.hpp
	src/Core/ECS/Factories/EntityFactory.cpp
	src/Core/ECS/Factories/EntityFactory.hpp
	src/Core/ECS/Factories/SystemFactory.cpp
	src/Core/ECS/Factories/SystemFactory.hpp
	src/Core/ECS/System.cpp
	src/Core/ECS/System.hpp
	src/Core/ECS/Systems/BlockedByTerrainSystem.cpp
	src/Core/ECS/Systems/BlockedByTerrainSystem.hpp
	src/Core/ECS/Systems/ControllableSystem.cpp
	src/Core/ECS/Systems/ControllableSystem.hpp
	src/Core/ECS/Systems/DisplayableSystem.cpp
	src/Core/ECS/Systems/DisplayableSystem.hpp
	src/Core/ECS/Systems/HealthSystem.cpp
	src/Core/ECS/Systems/HealthSystem.hpp
	src/Core/ECS/Systems/ManaSystem.cpp
	src/Core/ECS/Systems/ManaSystem.hpp
	src/Core/ECS/Systems/MovableSystem.cpp
	src/Core/ECS/Systems/MovableSystem.hpp
	src/Core/ECS/Systems/PlayerHudSystem.cpp
	src/Core/ECS/Systems/PlayerHudSystem.hpp
	src/Core/ECS/Systems/UselessSystem.cpp
	src/Core/ECS/Systems/UselessSystem.hpp
	src/Core/Exceptions.cpp
	src/Core/Exceptions.hpp
	src/Core/Resources/Game.hpp
	src/Core/Input/Input.cpp
	src/Core/Input/Input.hpp
	src/Core/Input/SFMLKeyboard.cpp
	src/Core/Input/SFMLKeyboard.hpp
	src/Core/Inventory/ClassicItem.cpp
	src/Core/Inventory/ClassicItem.hpp
	src/Core/Inventory/Item.cpp
	src/Core/Inventory/Item.hpp
	src/Core/Inventory/ItemFactory.cpp
	src/Core/Inventory/ItemFactory.hpp
	src/Core/Loading/Loader.cpp
	src/Core/Loading/Loader.hpp
	src/Core/Resources/Logger.cpp
	src/Core/Resources/Logger.hpp
	src/Core/Resources/Map.cpp
	src/Core/Resources/Map.hpp
	src/Core/Menus/Exceptions.hpp
	src/Core/Menus/Menu.cpp
	src/Core/Menus/Menu.hpp
	src/Core/Menus/MenuMgr.cpp
	src/Core/Menus/MenuMgr.hpp
	src/Core/Utils/NotCopyable.hpp
	src/Core/Rendering/Entity.cpp
	src/Core/Rendering/Entity.hpp
	src/Core/Rendering/Exceptions.hpp
	src/Core/Rendering/Hud.cpp
	src/Core/Rendering/Hud.hpp
	src/Core/Rendering/Screen.cpp
	src/Core/Rendering/Screen.hpp
	src/Core/Resources/Resources.cpp
	src/Core/Resources/Resources.hpp
	src/Core/Utils/Utils.cpp
	src/Core/Utils/Utils.hpp
	src/Core/Dialogs/DialogMgr.cpp
	src/Core/Dialogs/DialogMgr.hpp
	src/Core/ECS/Components/InteractComponent.cpp
	src/Core/ECS/Components/InteractComponent.hpp
	src/Core/ECS/Components/CollisionComponent.cpp
	src/Core/ECS/Components/CollisionComponent.hpp
	src/Core/ECS/Systems/CollisionSystem.cpp
	src/Core/ECS/Systems/CollisionSystem.hpp
	src/Core/ECS/Components/ColliderComponent.cpp
	src/Core/ECS/Components/ColliderComponent.hpp
	src/Core/ECS/Components/DialogComponent.cpp
	src/Core/ECS/Components/DialogComponent.hpp
	src/Core/ECS/Systems/DialogSystem.cpp
	src/Core/ECS/Systems/DialogSystem.hpp
	src/Core/ECS/Components/ShootComponent.cpp
	src/Core/ECS/Components/ShootComponent.hpp
	src/Core/ExternalCode/ExternalModule.hpp
	src/Core/ExternalCode/DynamicLibrary.cpp
	src/Core/ExternalCode/DynamicLibrary.hpp
	src/Core/Resources/Game.cpp
	src/Core/ECS/Systems/ShootSystem.cpp
	src/Core/ECS/Systems/ShootSystem.hpp
	src/Core/ECS/Components/OobDieComponent.cpp
	src/Core/ECS/Components/OobDieComponent.hpp
	src/Core/ECS/Systems/OobDieSystem.cpp
	src/Core/ECS/Systems/OobDieSystem.hpp
	src/Core/ECS/Quadtree/Quadtree.cpp
	src/Core/ECS/Quadtree/Quadtree.hpp
	src/Core/DataType/Rect.hpp
	src/Core/ECS/Quadtree/CircleCollider.cpp
	src/Core/ECS/Quadtree/CircleCollider.hpp
	src/Core/ECS/Quadtree/RectangleCollider.cpp
	src/Core/ECS/Quadtree/RectangleCollider.hpp
	src/Core/ECS/Quadtree/ICollider.hpp
	src/Core/ECS/Quadtree/ICollider.cpp
	src/Core/Input/SFMLJoypad.cpp
	src/Core/Input/SFMLJoypad.hpp
	src/Core/ECS/Components/ExperienceComponent.cpp
	src/Core/ECS/Components/ExperienceComponent.hpp
	src/Core/ECS/Systems/ExperienceSystem.cpp
	src/Core/ECS/Systems/ExperienceSystem.hpp
	src/Core/Loading/CardTree.cpp
	src/Core/Loading/CardTree.hpp
	src/Core/ECS/Components/DeckComponent.cpp
	src/Core/ECS/Components/DeckComponent.hpp
	src/Core/ECS/Systems/DeckSystem.cpp
	src/Core/ECS/Systems/DeckSystem.hpp
	src/Core/ExternalCode/LuaCode.cpp
	src/Core/ExternalCode/LuaCode.hpp
	src/Core/LuaObjects/LuaUserData.cpp
	src/Core/LuaObjects/LuaUserData.hpp
	src/Core/Utils/BaseObject.hpp
	src/Core/ExternalCode/ExternalModuleFactory.cpp
	src/Core/ExternalCode/ExternalModuleFactory.hpp
)

if (WIN32)
	target_link_libraries(
		THFgame-core
		sfml-window
		sfml-system
		sfml-graphics
		sfml-audio
		lua
	)
else (WIN32)
	target_link_libraries(
		THFgame-core
		sfml-window
		sfml-system
		sfml-graphics
		sfml-audio
		dl
		lua
	)
endif (WIN32)

#_____________________________________________________________

add_executable(
	map_editor
	${MAP_EDITOR_ICON}
	src/MapEditor/main.cpp
	src/MapEditor/MapEditor.cpp
	src/MapEditor/MapEditor.hpp
	src/MapEditor/Menus/MainMenu.cpp
	src/MapEditor/Menus/MainMenu.hpp
	src/MapEditor/GuiUtils.cpp
	src/MapEditor/GuiUtils.hpp
	src/MapEditor/ComponentGui.cpp
	src/MapEditor/ComponentGui.hpp
	src/Core/DataType/Vector.hpp
)

target_link_libraries(
	map_editor
	THFgame-core
	tgui
)

#_____________________________________________________________

add_library(
	test_attack MODULE
	src/BattleScripts/test_attack.cpp
)

target_link_libraries(
	test_attack
	THFgame-core
)
set_target_properties(test_attack PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/battle_scripts" PREFIX "")

#_____________________________________________________________

add_executable(
	THFgame
	${GAME_ICON}
	src/Game/main.cpp
	src/Game/Menus/InGameMenu.cpp
	src/Game/Menus/InGameMenu.hpp
	src/Game/Menus/InventoryMenu.cpp
	src/Game/Menus/InventoryMenu.hpp
	src/Game/Menus/MainMenu.cpp
	src/Game/Menus/MainMenu.hpp
)

target_link_libraries(
	THFgame
	THFgame-core
)

add_dependencies(
	THFgame
	test_attack
)
