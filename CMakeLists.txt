cmake_minimum_required(VERSION 3.13)
project(THFgame)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(
	THFgame
	src/main.cpp
	src/Logger.cpp
	src/Logger.hpp
	src/Screen.cpp
	src/Screen.hpp
	src/Resources.hpp src/Game.hpp)

target_link_libraries(
	THFgame
	sfml-window
	sfml-system
	sfml-graphics
)