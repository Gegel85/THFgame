#
# A CMake module to find glm
#
# Once done this module will define:
#  glm_FOUND - system has glm
#  glm_INCLUDE_DIRS - the glm include directory
#

IF (NOT glm_INCLUDE_DIRS)
    FIND_PATH(glm_INCLUDE_DIRS
        NAMES
            glm/glm.hpp
        PATHS
            "C:/Graphics/Tools/glm"       # Default Windows directory
            /usr/include/                 # Default Fedora28 system include path
            /usr/local/include/           # Default Fedora28 local include path
            ${CMAKE_MODULE_PATH}/include/ # Expected to contain the path to this file for Windows10
            ${glm_DIR}/include/           # glm root directory (if provided)
            ${glm_DIR}                    # glm root directory (if provided)
    )
ENDIF (NOT glm_INCLUDE_DIRS)

IF (glm_INCLUDE_DIRS)
    SET(glm_FOUND TRUE)
ELSE (glm_INCLUDE_DIRS)
    SET(glm_FOUND FALSE)
ENDIF (glm_INCLUDE_DIRS)

IF (glm_FIND_REQUIRED AND NOT glm_FOUND)
    MESSAGE(FATAL_ERROR
            "  glm not found.\n"
            "      Fill CMake variable glm_DIR to the provided directory.\n"
            )
ENDIF (glm_FIND_REQUIRED AND NOT glm_FOUND)