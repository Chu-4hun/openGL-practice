This is a pet project created to explore and learn OpenGL. The project aims to provide a simple and educational introduction to graphics programming using OpenGL.

## Table of Contents

- [Overview](#Overview)
- [Features](#Features)
- [Getting Started](#Getting_Started)
    - [Prerequisites](#Prerequisites)
    - [Building and Running](#Building_and_Running)
- [Project Structure](#Project_Structure)
- [Dependencies](#Dependencies)
- [Contributing](#Contributing)
- [License](#License)
- [Acknowledgments](#Acknowledgments)

## Overview

The Pet Learning OpenGL Project is designed to serve as a hands-on learning experience for OpenGL.

## Features

- Basic rendering using OpenGL.
- Simple shader programs for vertex and fragment processing.
- Structured project layout for ease of understanding.

## Getting Started

### Prerequisites

Before running the project, ensure you have the following installed:

- CMake
- Your preferred C++ compiler

### Building and Running

1. Clone the repository:
 ```bash
git clone --recursive https://github.com/Chu-4hun/openGL-practice.git
```
    
2. Navigate to the project directory:
```bash
cd openGL-practice
```
3. Run the bootstrap script to build vcpkg:
```bash
.\vcpkg\bootstrap-vcpkg.bat
```
4. install dependencies
```bash 
.\vcpkg\vcpkg install
```

## Project Structure

The project is structured as follows:

```
+---Engine
|   +---Platform
|   +---Renderer
+---res
|   +---shaders
```


## Dependencies

The project relies on the following dependencies:

- [GLFW](https://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)
- [SDL2](https://www.libsdl.org/)
* Build dependencies
	- [vcpkg](https://vcpkg.io/en/)
	- [Cmake](https://cmake.org/)


## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvement, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE]() file for details.

## Acknowledgments

- [OpenGl Docs](https://docs.gl/)
- [LearnOpenGL](https://learnopengl.com/) for tutorials and insights.
- [Hubr](https://habr.com/ru/articles/311808/) russian translation of [LearnOpenGL](https://learnopengl.com/)
- [Cherno youtube](https://www.youtube.com/@TheCherno) the c++ wizard