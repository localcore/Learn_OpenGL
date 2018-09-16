cmake_minimum_required(VERSION 3.12)
project(Learn_OpenGL_GLFW)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(GLFW)

link_libraries(glfw)
include_directories(GLFW/deps)

add_subdirectory(vendor/glm)

add_executable(Learn_OpenGL main.cpp
        VertexBuffer.cpp VertexBufferLayout.h
        IndexBuffer.cpp VertexArray.cpp Shader.cpp Texture.cpp
        Renderer.cpp
        #vendor/stb_image/stb.h
        #vendor/glm/glm.hpp
        #vendor/glm/gtc/matrix_transform.hpp

        GLFW/deps/glad/glad.h
        GLFW/deps/glad.c)


#target_link_libraries(Learn_OpenGL_GLFW glfw ${GLFW_LIBRARIES})
#target_link_libraries(Learn_OpenGL_GLFW glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})