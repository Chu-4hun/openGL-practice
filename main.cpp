#include <iostream>

#include <GL/glew.h>
#include "SDL2/SDL.h"

#undef main

#include "SDL_opengl.h"


int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_Window *window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                                          SDL_WINDOW_OPENGL);

    if (window == nullptr) {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    glewExperimental = GL_TRUE;
    auto init_res = glewInit();
    auto ctx = SDL_GL_CreateContext(window);

    if (init_res != GLEW_OK) {
        std::cout << glewGetErrorString(glewInit()) << std::endl;
    }

    bool should_run = true;
    while (should_run) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE) {
                should_run = false;
                break;
            }
        }
    }

    return 0;
}

//int Cleanup() {
//    glUseProgram(0);
//    glDisableVertexAttribArray(0);
//    glDetachShader(m_shader_prog, m_vert_shader);
//    glDetachShader(m_shader_prog, m_frag_shader);
//    glDeleteProgram(m_shader_prog);
//    glDeleteShader(m_vert_shader);
//    glDeleteShader(m_frag_shader);
//    glDeleteTextures(1, &m_tex);
//    glDeleteBuffers(1, &m_ebo);
//    glDeleteBuffers(1, &m_vbo);
//    glDeleteVertexArrays(1, &m_vao);
//    SDL_GL_DeleteContext(m_context);
//    SDL_DestroyWindow(m_window);
//    SDL_Quit();
//    return 0;
//}
