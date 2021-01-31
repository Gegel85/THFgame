#
# A CMake module to find OpenGL
#
# Once done this module will define:
#  OpenGL_FOUND - system has OpenGL
#  OpenGL_LIBRARIES - Link these to use OpenGL
#

if (WIN32)
        set(OpenGL_LIBRARIES opengl32)
else (WIN32)
        set(OpenGL_LIBRARIES GL)
endif (WIN32)