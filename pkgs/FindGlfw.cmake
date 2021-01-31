#
# A CMake module to find Glfw
#
# Once done this module will define:
#  Glfw_FOUND - system has Glfw
#  Glfw_LIBRARIES - Link these to use Glfw
#

IF (NOT Glfw_INCLUDE_DIRS OR NOT Glfw_LIBRARIES)
        IF (MSVC)      # Visual Studio
                SET(CMAKE_FIND_LIBRARY_PREFIXES ";lib")
                SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib;.dll.lib;.dll.a;.a")
        ELSEIF (MINGW) # Windows
                SET(CMAKE_FIND_LIBRARY_PREFIXES ";lib")
                SET(CMAKE_FIND_LIBRARY_SUFFIXES ".dll.a;.dll;.a;.lib")
        ELSE (MSVC)    # Linux
                SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
                SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so;.a")
        ENDIF(MSVC)

        FIND_LIBRARY(Glfw_LIBRARIES
                NAMES
                glfw
                glfw3
                PATHS
                "C:/Graphics/Tools/glfw/lib"  # Default Windows directory
                ${Glfw_DIR}/lib/              # Glfw root directory (if provided)
                ${Glfw_DIR}                   # Glfw root directory (if provided)
                /usr/lib64/                   # Default Fedora28 library path
                /usr/lib/                     # Some more Linux library path
                /usr/lib/x86_64-linux-gnu/    # Some more Linux library path
                /usr/local/lib/               # Some more Linux library path
                /usr/local/lib64/             # Some more Linux library path
        )

        FIND_PATH(Glfw_INCLUDE_DIRS
                NAMES
                GLFW/glfw3.h
                PATHS
                "C:/Graphics/Tools/glfw/include" # Default Windows directory
                /usr/include/                    # Default Fedora28 system include path
                /usr/local/include/              # Default Fedora28 local include path
                ${CMAKE_MODULE_PATH}/include/    # Expected to contain the path to this file for Windows10
                ${Glfw_DIR}/include/             # Glfw root directory (if provided)
                ${Glfw_DIR}                      # Glfw root directory (if provided)
        )
ENDIF (NOT Glfw_INCLUDE_DIRS OR NOT Glfw_LIBRARIES)

IF (Glfw_INCLUDE_DIRS AND Glfw_LIBRARIES)
        SET(Glfw_FOUND TRUE)
ELSE (Glfw_INCLUDE_DIRS AND Glfw_LIBRARIES)
        SET(Glfw_FOUND FALSE)
ENDIF (Glfw_INCLUDE_DIRS AND Glfw_LIBRARIES)

IF (Glfw_FIND_REQUIRED AND NOT Glfw_FOUND)
        MESSAGE(FATAL_ERROR
                "  Glfw not found.\n"
                "      Fill CMake variable Glfw_DIR to the provided directory.\n"
                )
ENDIF (Glfw_FIND_REQUIRED AND NOT Glfw_FOUND)