#include <iostream>

// #include "renderer/Shader.h"
#include <fstream>
#include <sstream>
#include <string>

#include "GL/glew.h"
#include "Platform/OpenGL/GLShader.h"
#include "Renderer/Window.h"
#include "SDL2/SDL.h"

// using ChuEngine::Shader; // In future this needs to be enabled
using ChuEngine::GLShader;

#undef main


GLfloat vertices[] = {
    // Позиции         // Цвета
    0.5f,  0.5f,  0.0f, /**/ 1.0f, 0.0f, 0.0f, // Нижний правый угол
    0.5f,  -0.5f, 0.0f, /**/ 0.0f, 1.0f, 0.0f, // Нижний левый угол
    -0.5f, -0.5f, 0.0f, /**/ 0.0f, 0.0f, 1.0f, // Верхний угол
    -0.5f, 0.5f,  0.0f, /**/ 1.0f, 0.0f, 1.0f  // Верхний угол
};
uint32_t indices[] = {
    0, 1, 3, // Первый треугольник
    1, 2, 3  // Второй треугольник
};

int main() {
    ChuEngine::Window _window{}; // It may crash but only if SDL could not be initialized
    auto window = _window.getSDLWindow();
    auto context = _window.context;

    if (!window) {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (!context) return 1;


    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    uint32_t VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    uint32_t EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glBindVertexArray(0);
    GLShader shader("../../res/shaders/base.glsl");

    shader.bind();

    bool should_run = true;
    bool wireframe_mode = false;

    while (should_run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(VAO);
//            glDrawArrays(GL_TRIANGLES, 0, 3);
            if (wireframe_mode) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);


            SDL_GL_SwapWindow(window);


            switch (event.type) {
            case SDL_QUIT:
                _window.close();
                should_run = false;
                break;
            case SDL_KEYDOWN:
                auto keys = SDL_GetKeyboardState(nullptr);
                if (keys[SDL_SCANCODE_ESCAPE]) {
                    _window.close();
                    should_run = false;
                }
                if (keys[SDL_SCANCODE_CAPSLOCK]) {
                    wireframe_mode = !wireframe_mode;
                }
                break;
            }
        }
    }

    return 0;
}