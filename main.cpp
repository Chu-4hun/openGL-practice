#include <iostream>

#include "SDL2/SDL.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <string>

#undef main



GLfloat vertices[] = {
    // Позиции         // Цвета
    0.5f,  0.5f, 0.0f,  /**/ 1.0f, 0.0f, 0.0f, // Нижний правый угол
     0.5f, -0.5f, 0.0f, /**/ 0.0f, 1.0f, 0.0f, // Нижний левый угол
    -0.5f, -0.5f, 0.0f, /**/ 0.0f, 0.0f, 1.0f, // Верхний угол
    -0.5f,  0.5f, 0.0f,  /**/ 1.0f, 0.0f, 1.0f  // Верхний угол
};
uint32_t indices[] = {
    0, 1, 3, // Первый треугольник
    1, 2, 3  // Второй треугольник
};

struct ShaderSources {
    std::string vertexSource;
    std::string fragmentSource;
};

static ShaderSources parseShader(const std::string& path) {
    std::ifstream stream(path);

    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (std::getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else
            ss[(int)type] << line << '\n';
    }
    return {ss[0].str(), ss[1].str()};
}

static unsigned int compileShader(const std::string& source, unsigned int shaderType) {
    uint32_t id = glCreateShader(shaderType);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)alloca(lenght * sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);
        std::cout << "Failed to compile shader"
                  << "\n";
        std::cout << message << "\n";
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static uint32_t createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    uint32_t program = glCreateProgram();
    uint32_t vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    uint32_t fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

SDL_Window* initWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_Window* window = SDL_CreateWindow(
        "SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
    );

    if (window == nullptr) {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return window;
}

void* initOpenGl(SDL_Window* window) {
    glewExperimental = GL_TRUE;
    auto init_res = glewInit();
    auto context = SDL_GL_CreateContext(window);

    if (init_res != GLEW_OK) {
        std::cout << glewGetErrorString(glewInit()) << std::endl;
    }
    return context;
}
void closeWindow(SDL_Window* window, void* context, uint32_t shader) {
    glDeleteProgram(shader);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    glUseProgram(0);
    SDL_Quit();
}


int main() {
    auto window = initWindow();
    if (!window) return 1;

    auto context = initOpenGl(window);
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

    ShaderSources sources = parseShader("../res/shaders/base.glsl");
    uint32_t shader = createShader(sources.vertexSource, sources.fragmentSource);

    glUseProgram(shader);


    bool should_run = true;
    while (should_run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(VAO);
            //                        glDrawArrays(GL_TRIANGLES, 0, 3);
            //            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);


            SDL_GL_SwapWindow(window);
            switch (event.type) {
            case SDL_QUIT:
                closeWindow(window, context, shader);
                should_run = false;
                break;
            case SDL_KEYDOWN:
                auto keys = SDL_GetKeyboardState(nullptr);
                if (keys[SDL_SCANCODE_ESCAPE]) {
                    closeWindow(window, context, shader);
                    should_run = false;
                }
                break;
            }
        }
    }

    return 0;
}