#include <iostream>

#include "SDL2/SDL.h"
#include <GL/glew.h>

#undef main


// Triangle vertices
float vertices[] = {
    -0.5f, -0.5f, 0.0f, //
    0.5f,  -0.5f, 0.0f, //
    0.0f,  0.5f,  0.0f,
};

SDL_Window* initWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_Window* window = SDL_CreateWindow(
        "SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL
    );

    if (window == nullptr) {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return window;
}

int main() {
    auto window = initWindow();
    if (!window) {
        return 0;
    }

    glewExperimental = GL_TRUE;
    auto init_res = glewInit();
    auto context = SDL_GL_CreateContext(window);

    if (init_res != GLEW_OK) {
        std::cout << glewGetErrorString(glewInit()) << std::endl;
    }

    bool should_run = true;
    GLint indicies[] = {0, 1, 2, 0, 2, 3};
    while (should_run) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE) {
                SDL_GL_DeleteContext(context);
                SDL_DestroyWindow(window);
                SDL_Quit();
                should_run = false;
                break;
            }
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indicies);
            SDL_GL_SwapWindow(window);
        }
    }

    return 0;
}

// int Cleanup() {
//     glUseProgram(0);
//     glDisableVertexAttribArray(0);
//     glDetachShader(m_shader_prog, m_vert_shader);
//     glDetachShader(m_shader_prog, m_frag_shader);
//     glDeleteProgram(m_shader_prog);
//     glDeleteShader(m_vert_shader);
//     glDeleteShader(m_frag_shader);
//     glDeleteTextures(1, &m_tex);
//     glDeleteBuffers(1, &m_ebo);
//     glDeleteBuffers(1, &m_vbo);
//     glDeleteVertexArrays(1, &m_vao);
//     SDL_GL_DeleteContext(m_context);
//     SDL_DestroyWindow(m_window);
//     SDL_Quit();
//     return 0;
// }
