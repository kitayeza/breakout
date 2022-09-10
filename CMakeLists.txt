cmake_minimum_required(VERSION 3.23)
project(breakout)

set(CMAKE_CXX_STANDARD 20)

#add_executable(breakout src/main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)

add_subdirectory(src/)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glew)
add_subdirectory(lib/glm)

add_executable(breakout ${SOURCES} src/Renderer.h src/Renderer.cpp src/utils.h src/Shader.h src/Shader.cpp src/GameObject.h src/GameObject.cpp)

# find_package(OpenGL REQUIRED)

target_link_libraries(breakout
        glfw
        libglew_static
        glm
        )
