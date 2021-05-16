#
# A CMake module to find LUA
#
# Once done this module will define:
#  LUA_FOUND - system has LUA
#  LUA_LIBRARIES
#  - Link these to use LUA
#  LUA_INCLUDE_DIRS
#  - Include directories
#

IF (NOT LUA_INCLUDE_DIRS OR NOT LUA_LIBRARIES)
        IF (MSVC)      # Visual Studio
                SET(CMAKE_FIND_LIBRARY_PREFIXES ";lib")
                SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib;.dll.lib;.dll.a;.a")
        ELSEIF (MINGW) # Windows
                SET(CMAKE_FIND_LIBRARY_PREFIXES ";lib")
                SET(CMAKE_FIND_LIBRARY_SUFFIXES ".dll.a;.dll;.a;.lib")
        ELSE (MSVC)    # Linux and MacOS
                SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
                SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so;.dylib;.a")
        ENDIF(MSVC)

        FIND_LIBRARY(LUA_LIBRARIES
                NAMES
                lua
                PATHS
                ${LUA_DIR}/lib/               # Lua root directory (if provided)
                ${LUA_DIR}                    # Lua root directory (if provided)
                /usr/lib64/                   # Default Fedora28 library path
                /usr/lib/                     # Some more Linux library path
                /usr/lib/x86_64-linux-gnu/    # Some more Linux library path
                /usr/local/lib/               # Some more Linux library path
                /usr/local/lib64/             # Some more Linux library path
        )

        FIND_PATH(LUA_INCLUDE_DIRS
                NAMES
                lua.hpp
                PATHS
                /usr/include/                     # Default Fedora28 system include path
                /usr/local/include/               # Default Fedora28 local include path
                /usr/include/lua                  # Default Fedora28 system include path
                /usr/local/include/lua            # Default Fedora28 local include path
                ${CMAKE_MODULE_PATH}/include/lua  # Expected to contain the path to this file for Windows10
                ${CMAKE_MODULE_PATH}/include/     # Expected to contain the path to this file for Windows10
                ${LUA_DIR}/include/lua            # Lua root directory (if provided)
                ${LUA_DIR}/lua                    # Lua root directory (if provided)
                ${LUA_DIR}/include/               # Lua root directory (if provided)
                ${LUA_DIR}                        # Lua root directory (if provided)
        )
ENDIF (NOT LUA_INCLUDE_DIRS OR NOT LUA_LIBRARIES)

IF (LUA_INCLUDE_DIRS AND LUA_LIBRARIES)
        SET(LUA_FOUND TRUE)
ELSE ()
        SET(LUA_FOUND FALSE)
ENDIF ()

IF (Lua_FIND_REQUIRED AND NOT LUA_FOUND)
        MESSAGE(FATAL_ERROR
                "  LUA not found.\n"
                "      Fill CMake variable LUA_DIR to the provided directory.\n"
                )
ENDIF (Lua_FIND_REQUIRED AND NOT LUA_FOUND)
