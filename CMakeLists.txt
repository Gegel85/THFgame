cmake_minimum_required(VERSION 3.13)
project(THFgame)

set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
	add_compile_options(-Wall -Wextra -W -g)
endif ()

add_executable(
	THFgame
	src/ECS/Component.cpp
	src/ECS/Component.hpp
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
	src/ECS/Systems/ControllableSystem.cpp
	src/ECS/Systems/ControllableSystem.hpp
	src/ECS/Systems/DisplayableSystem.cpp
	src/ECS/Systems/DisplayableSystem.hpp
	src/ECS/Systems/MovableSystem.cpp
	src/ECS/Systems/MovableSystem.hpp
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
)

target_link_libraries(
	THFgame
	sfml-window
	sfml-system
	sfml-graphics
	sfml-audio
)