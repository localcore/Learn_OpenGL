cmake_minimum_required(VERSION 3.12)
project(Learn_OpenGL_GLFW)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(GLFW)

link_libraries(glfw)
include_directories(GLFW/include)
include_directories(GLFW/deps)
#include_directories(${GLFW_SOURCE_DIR}/include)
#include_directories(${GLFW_SOURCE_DIR}/deps)

set(GLAD "${GLFW_SOURCE_DIR}/deps/glad/glad.h"
        "${GLFW_SOURCE_DIR}/deps/glad.c" Renderer.h Renderer.cpp VertexBuffer.cpp VertexArray.cpp VertexBufferLayout.cpp VertexBufferLayout.h)

add_executable(Learn_OpenGL main.cpp Renderer.cpp VertexBuffer.cpp IndexBuffer.cpp VertexArray.cpp VertexBufferLayout.cpp ${GLAD})

#target_link_libraries(Learn_OpenGL_GLFW glfw ${GLFW_LIBRARIES})
#target_link_libraries(Learn_OpenGL_GLFW glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})