cmake_minimum_required(VERSION 3.13)
project(THFgame)

set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
	add_compile_options(-Wall -Wextra -W -g)
endif()

include_directories(include)

add_executable(
	THFgame
	src/main.cpp
	src/Logger.cpp
	src/Logger.hpp
	src/Rendering/Screen.cpp
	src/Rendering/Screen.hpp
	src/Resources.hpp
	src/Game.hpp
	src/Resources.cpp
	src/Loader.cpp
	src/Loader.hpp
	src/Menu.cpp
	src/Menu.hpp
	src/Map.cpp
	src/Map.hpp
	src/ECS/Entity.cpp
	src/ECS/Entity.hpp
	src/Exceptions.hpp
	src/ECS/Core.cpp
	src/ECS/Core.hpp
	src/ECS/Component.cpp
	src/ECS/Component.hpp
	src/ECS/System.cpp
	src/ECS/System.hpp
	src/Exceptions.cpp
	src/ECS/Exceptions.hpp
	src/Rendering/Exceptions.hpp
	src/Rendering/Entity.hpp
	src/Rendering/Entity.cpp
	src/ECS/Factories/EntityFactory.cpp src/ECS/Factories/EntityFactory.hpp src/ECS/Components/PositionComponent.hpp src/ECS/Components/PositionComponent.cpp src/ECS/Components/DisplayableComponent.cpp src/ECS/Components/DisplayableComponent.hpp src/ECS/Systems/DisplayableSystem.cpp src/ECS/Systems/DisplayableSystem.hpp src/ECS/Factories/SystemFactory.cpp src/ECS/Factories/SystemFactory.hpp src/Input.cpp src/Input.hpp src/Input/Keyboard.cpp src/Input/Keyboard.hpp src/ECS/Components/ControllableComponent.cpp src/ECS/Components/ControllableComponent.hpp src/ECS/Systems/ControllableSystem.cpp src/ECS/Systems/ControllableSystem.hpp src/ECS/Components/MovableComponent.cpp src/ECS/Components/MovableComponent.hpp src/ECS/Systems/MovableSystem.cpp src/ECS/Systems/MovableSystem.hpp)

target_link_libraries(
	THFgame
	sfml-window
	sfml-system
	sfml-graphics
	sfml-audio
)