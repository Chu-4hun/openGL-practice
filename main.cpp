#include <iostream>

// #include "renderer/Shader.h"
#include <fstream>
#include <string>

#include "GL/glew.h"
#include "Platform/OpenGL/GLObject.h"
#include "Platform/OpenGL/GLShader.h"
#include "Renderer/Window.h"
#include "SDL2/SDL.h"


#include <glm/gtc/type_ptr.hpp>

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
    const auto window = _window.getSDLWindow();
    const auto context = _window.context;

    if (!window) {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (!context) return 1;

    const ChuEngine::GLObject rainbow_quad(
        {
            {
             {0.5f, 0.5f, 0.0f},
             {1.0f, 0.0f, 0.0f},

             },
            {
             {0.5f, -0.5f, 0.0f},
             {0.0f, 1.0f, 0.0f},
             },
            {
             {-0.5f, -0.5f, 0.0f},
             {0.0f, 0.0f, 1.0f},

             },
            {
             {-0.5f, 0.5f, 0.0f},
             {1.0f, 0.0f, 1.0f},

             },
    },
        {0, 1, 3, 1, 2, 3}, GL_STATIC_DRAW
    );


    const GLShader shader("../../res/shaders/base.glsl");

    shader.bind();

    bool should_run = true;
    bool wireframe_mode = false;

    while (should_run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                _window.close();
                should_run = false;
                break;
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    glViewport(0, 0, event.window.data1, event.window.data2);
                }
                break;
            }
            case SDL_KEYDOWN:
                const auto keys = SDL_GetKeyboardState(nullptr);
                if (keys[SDL_SCANCODE_ESCAPE]) {
                    _window.close();
                    should_run = false;
                }
                if (keys[SDL_SCANCODE_CAPSLOCK]) {
                    wireframe_mode = !wireframe_mode;
                }
                break;
            }
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // glBindVertexArray(1);
            glBindVertexArray(rainbow_quad.getVAO());
            // glDrawArrays(GL_TRIANGLES, 0, 3);
            if (wireframe_mode) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);


            SDL_GL_SwapWindow(window);
        }
    }

    return 0;
}
