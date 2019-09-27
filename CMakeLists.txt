cmake_minimum_required(VERSION 3.13)
project(THFgame)

set(CMAKE_CXX_STANDARD 17)

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
	src/Exceptions.hpp src/ECS/Core.cpp src/ECS/Core.hpp src/ECS/Component.cpp src/ECS/Component.hpp src/ECS/System.cpp src/ECS/System.hpp src/Exceptions.cpp src/ECS/Exceptions.hpp)

target_link_libraries(
	THFgame
	sfml-window
	sfml-system
	sfml-graphics
	sfml-audio
)