#
# A CMake module to find Glew
#
# Once done this module will define:
#  Glew_FOUND - system has Glew
#  Glew_LIBRARIES - Link these to use Glew
#

IF (NOT Glew_INCLUDE_DIRS OR NOT Glew_LIBRARIES)
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

        FIND_LIBRARY(Glew_LIBRARIES
                NAMES
                GLEW
                glew32
                PATHS
                "C:/Graphics/Tools/glew/lib"  # Default Windows directory
                ${Glew_DIR}/lib/              # Glew root directory (if provided)
                ${Glew_DIR}                   # Glew root directory (if provided)
                /usr/lib64/                   # Default Fedora28 library path
                /usr/lib/                     # Some more Linux library path
                /usr/lib/x86_64-linux-gnu/    # Some more Linux library path
                /usr/local/lib/               # Some more Linux library path
                /usr/local/lib64/             # Some more Linux library path
        )

        FIND_PATH(Glew_INCLUDE_DIRS
                NAMES
                GL/glew.h
                PATHS
                "C:/Graphics/Tools/glew/include" # Default Windows directory
                /usr/include/                    # Default Fedora28 system include path
                /usr/local/include/              # Default Fedora28 local include path
                ${CMAKE_MODULE_PATH}/include/    # Expected to contain the path to this file for Windows10
                ${Glew_DIR}/include/             # Glew root directory (if provided)
                ${Glew_DIR}                      # Glew root directory (if provided)
        )
ENDIF (NOT Glew_INCLUDE_DIRS OR NOT Glew_LIBRARIES)

IF (Glew_INCLUDE_DIRS AND Glew_LIBRARIES)
        SET(Glew_FOUND TRUE)
ELSE (Glew_INCLUDE_DIRS AND Glew_LIBRARIES)
        SET(Glew_FOUND FALSE)
ENDIF (Glew_INCLUDE_DIRS AND Glew_LIBRARIES)

IF (Glew_FIND_REQUIRED AND NOT Glew_FOUND)
        MESSAGE(FATAL_ERROR
                "  Glew not found.\n"
                "      Fill CMake variable Glew_DIR to the provided directory.\n"
                )
ENDIF (Glew_FIND_REQUIRED AND NOT Glew_FOUND)

IF (NOT ${Glew_INCLUDE_DIRS} STREQUAL "C:/Graphics/Tools/glew/include" AND WIN32)
        MESSAGE(WARNING "Glew library is not in the standard location ! (${Glew_INCLUDE_DIRS})\nMove it to C:/Graphics/Tools/glew/include\n")
ENDIF ()