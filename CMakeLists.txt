cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(chu_engine VERSION 0.1.0 LANGUAGES C CXX)

#include()
find_package(fmt CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)


add_executable(${PROJECT_NAME} main.cpp
        Engine/Renderer/Shader.cpp
        Engine/Renderer/Shader.h
        Engine/Platform/OpenGL/GLShader.cpp
        Engine/Platform/OpenGL/GLShader.h
        Engine/Platform/OpenGL/GLVertex.cpp
        Engine/Platform/OpenGL/GLVertex.h
        Engine/Platform/OpenGL/GLVertex.h
        Engine/Renderer/Window.cpp
        Engine/Renderer/Window.h
        Engine/Renderer/Window.h
)
target_include_directories(${PROJECT_NAME} PRIVATE Engine)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        GLEW::GLEW
        glm::glm
        )


#        sfml-system sfml-network sfml-graphics sfml-window)

