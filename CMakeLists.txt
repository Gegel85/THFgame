cmake_minimum_required(VERSION 3.10)
project(THFgame)

set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
	add_compile_options(-Wall -Wextra -W -g)
endif ()

include_directories(nlohmann)

add_executable(
	THFgame
	src/ECS/Component.cpp
	src/ECS/Component.hpp
	src/ECS/Components/BlockedByTerrainComponent.cpp
	src/ECS/Components/BlockedByTerrainComponent.hpp
	src/ECS/Components/ControllableComponent.cpp
	src/ECS/Components/ControllableComponent.hpp
	src/ECS/Components/DisplayableComponent.cpp
	src/ECS/Components/DisplayableComponent.hpp
	src/ECS/Components/MovableComponent.cpp
	src/ECS/Components/MovableComponent.hpp
	src/ECS/Components/PositionComponent.cpp
	src/ECS/Components/PositionComponent.hpp
	src/ECS/Core.cpp
	src/ECS/Core.hpp
	src/ECS/Entity.cpp
	src/ECS/Entity.hpp
	src/ECS/Exceptions.hpp
	src/ECS/Factories/EntityFactory.cpp
	src/ECS/Factories/EntityFactory.hpp
	src/ECS/Factories/SystemFactory.cpp
	src/ECS/Factories/SystemFactory.hpp
	src/ECS/System.cpp
	src/ECS/System.hpp
	src/ECS/Systems/BlockedByTerrainSystem.cpp
	src/ECS/Systems/BlockedByTerrainSystem.hpp
	src/ECS/Systems/ControllableSystem.cpp
	src/ECS/Systems/ControllableSystem.hpp
	src/ECS/Systems/DisplayableSystem.cpp
	src/ECS/Systems/DisplayableSystem.hpp
	src/ECS/Systems/MovableSystem.cpp
	src/ECS/Systems/MovableSystem.hpp
	src/ECS/Systems/UselessSystem.cpp
	src/ECS/Systems/UselessSystem.hpp
	src/Exceptions.cpp
	src/Exceptions.hpp
	src/Game.hpp
	src/Input.cpp
	src/Input.hpp
	src/Input/Keyboard.cpp
	src/Input/Keyboard.hpp
	src/Loader.cpp
	src/Loader.hpp
	src/Logger.cpp
	src/Logger.hpp
	src/main.cpp
	src/Map.cpp
	src/Map.hpp
	src/Menu.cpp
	src/Menu.hpp
	src/Rendering/Entity.cpp
	src/Rendering/Entity.hpp
	src/Rendering/Exceptions.hpp
	src/Rendering/Screen.cpp
	src/Rendering/Screen.hpp
	src/Resources.cpp
	src/Resources.hpp
	src/Utils.hpp
	src/Utils.cpp
	src/NotCopyable.hpp
	src/ECS/Factories/ComponentFactory.cpp
	src/ECS/Factories/ComponentFactory.hpp
	src/ECS/Components/HealthComponent.cpp
	src/ECS/Components/HealthComponent.hpp
	src/ECS/Components/ManaComponent.cpp src/ECS/Components/ManaComponent.hpp src/ECS/Systems/HealthSystem.cpp src/ECS/Systems/HealthSystem.hpp src/ECS/Systems/ManaSystem.cpp src/ECS/Systems/ManaSystem.hpp src/ECS/Components/NameComponent.cpp src/ECS/Components/NameComponent.hpp src/ECS/Components/PlayerHudComponent.cpp src/ECS/Components/PlayerHudComponent.hpp src/ECS/Components/BasicSerializeComponent.cpp src/ECS/Components/BasicSerializeComponent.hpp src/ECS/Systems/PlayerHudSystem.cpp src/ECS/Systems/PlayerHudSystem.hpp src/Rendering/Hud.cpp src/Rendering/Hud.hpp)

target_link_libraries(
	THFgame
	sfml-window
	sfml-system
	sfml-graphics
	sfml-audio
)
