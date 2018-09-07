cmake_minimum_required(VERSION 3.12)
project(Learn_OpenGL_GLFW)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(GLFW)

link_libraries(glfw)
include_directories(GLFW/include)
include_directories(GLFW/deps)
#include_directories(${GLFW_SOURCE_DIR}/include)
#include_directories(${GLFW_SOURCE_DIR}/deps)

set(GLAD "${GLFW_SOURCE_DIR}/deps/glad/glad.h"
        "${GLFW_SOURCE_DIR}/deps/glad.c")

add_executable(Learn_OpenGL main.cpp ${GLAD})

#target_link_libraries(Learn_OpenGL_GLFW glfw ${GLFW_LIBRARIES})
#target_link_libraries(Learn_OpenGL_GLFW glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})