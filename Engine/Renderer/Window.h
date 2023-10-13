//
// Created by Belocurov Dan on 13.10.2023.
//
#include "SDL2/SDL.h"

#pragma once
namespace ChuEngine {
    class Window {
      public:
        Window();
        ~Window();
        void close();
        SDL_Window* getSDLWindow();

      private:
        static void closeWindow(SDL_Window* window, void* context);
        static void* initContext(SDL_Window* window);

      private:
      public:
        SDL_Window* window;
        void* context;
    };


} // namespace ChuEngine
