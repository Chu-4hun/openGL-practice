//
// Created by Belocurov Dan on 13.10.2023.
//

#include "Window.h"
#include "GL/glew.h"
#include <iostream>

namespace ChuEngine {

    void Window::closeWindow(SDL_Window* window, void* context) {
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        glUseProgram(0);
        SDL_Quit();
    }

    void* Window::initContext(SDL_Window* window) {
        glewExperimental = GL_TRUE;
        auto init_res = glewInit();
        auto context = SDL_GL_CreateContext(window);

        if (init_res != GLEW_OK) {
            std::cout << glewGetErrorString(glewInit()) << std::endl;
        }
        return context;
    }

    Window::Window() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
            throw; // I want it to crash here because SDL is the critical part
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        this->window = SDL_CreateWindow(
            "SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
        );
        this->context = initContext(this->window);
    }

    Window::~Window() { closeWindow(this->window, this->context); }


    void Window::close() { closeWindow(this->window, this->context); }

    SDL_Window* Window::getSDLWindow() { return this->window; }
} // namespace ChuEngine