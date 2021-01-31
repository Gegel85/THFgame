#
# A CMake module to find Assimp
#
# Once done this module will define:
#  Assimp_FOUND - system has Assimp
#  Assimp_LIBRARIES - Link these to use Assimp
#

IF (NOT Assimp_INCLUDE_DIRS OR NOT Assimp_LIBRARIES)
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

        FIND_LIBRARY(Assimp_LIBRARIES
                NAMES
                assimp
                PATHS
                "C:/Graphics/Tools/Assimp/lib/x86"  # Default Windows directory
                ${Assimp_DIR}/lib/x86               # Assimp root directory (if provided)
                ${Assimp_DIR}/lib                   # Assimp root directory (if provided)
                ${Assimp_DIR}                       # Assimp root directory (if provided)
                /usr/lib64/                         # Default Fedora28 library path
                /usr/lib/                           # Some more Linux library path
                /usr/lib/x86_64-linux-gnu/          # Some more Linux library path
                /usr/local/lib/                     # Some more Linux library path
                /usr/local/lib64/                   # Some more Linux library path
        )

        FIND_PATH(Assimp_INCLUDE_DIRS
                NAMES
                assimp/Importer.hpp
                PATHS
                "C:/Graphics/Tools/Assimp/include" # Default Windows directory
                /usr/include/                      # Default Fedora28 system include path
                /usr/local/include/                # Default Fedora28 local include path
                ${CMAKE_MODULE_PATH}/include/      # Expected to contain the path to this file for Windows10
                ${Assimp_DIR}/include/             # Assimp root directory (if provided)
                ${Assimp_DIR}                      # Assimp root directory (if provided)
        )
ENDIF (NOT Assimp_INCLUDE_DIRS OR NOT Assimp_LIBRARIES)

IF (Assimp_INCLUDE_DIRS AND Assimp_LIBRARIES)
        SET(Assimp_FOUND TRUE)
ELSE (Assimp_INCLUDE_DIRS AND Assimp_LIBRARIES)
        SET(Assimp_FOUND FALSE)
ENDIF (Assimp_INCLUDE_DIRS AND Assimp_LIBRARIES)

IF (Assimp_FIND_REQUIRED AND NOT Assimp_FOUND)
        MESSAGE(FATAL_ERROR
                "  Assimp not found.\n"
                "      Fill CMake variable Assimp_DIR to the provided directory.\n"
                )
ENDIF (Assimp_FIND_REQUIRED AND NOT Assimp_FOUND)