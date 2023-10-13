//
// Created by Belocurov Dan on 10.08.2023.
//

#include "GLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include "GL/glew.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

namespace ChuEngine {
    GLShader::GLShader(const std::string& filepath) {
        auto shaderSources = parseShader(filepath);

        Id = glCreateProgram();
        uint32_t vs = compileShader(shaderSources.vertexSource, GL_VERTEX_SHADER);
        uint32_t fs = compileShader(shaderSources.fragmentSource, GL_FRAGMENT_SHADER);

        glAttachShader(Id, vs);
        glAttachShader(Id, fs);
        glLinkProgram(Id);
        glValidateProgram(Id);

        glDeleteShader(vs);
        glDeleteShader(fs);
    }
    GLShader::GLShader(
        std::string name,             //
        const std::string& vertexSrc, //
        const std::string& fragmentSrc
    )
        : Name(std::move(name)) {

        Id = glCreateProgram();
        uint32_t vs = compileShader(vertexSrc, GL_VERTEX_SHADER);
        uint32_t fs = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);

        glAttachShader(Id, vs);
        glAttachShader(Id, fs);
        glLinkProgram(Id);
        glValidateProgram(Id);

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    ShaderSources GLShader::parseShader(const std::string& path) {
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

    unsigned int GLShader::compileShader(const std::string& source, unsigned int shaderType) {
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
    GLShader::~GLShader() { glDeleteProgram(Id); }
    void GLShader::bind() const { glUseProgram(Id); }
    void GLShader::unbind() const { glUseProgram(0); }

    void GLShader::setInt(const std::string& name, int value) {
        glUniform1i(glGetUniformLocation(Id, name.c_str()), value);
    }

    void GLShader::setIntArray(const std::string& name, int* values, uint32_t count) {
        uploadUniformIntArray(name, values, count);
    }

    void GLShader::setFloat(const std::string& name, float value) {
        uploadUniformFloat(name, value);
    }

    void GLShader::setFloat2(const std::string& name, const glm::vec2& value) {
        uploadUniformFloat2(name, value);
    }

    void GLShader::setFloat3(const std::string& name, const glm::vec3& value) {

        uploadUniformFloat3(name, value);
    }

    void GLShader::setFloat4(const std::string& name, const glm::vec4& value) {
        uploadUniformFloat4(name, value);
    }

    void GLShader::setMat4(const std::string& name, const glm::mat4& value) {
        uploadUniformMat4(name, value);
    }

    void GLShader::uploadUniformInt(const std::string& name, int value) {
        GLint location = glGetUniformLocation(Id, name.c_str());
        glUniform1i(location, value);
    }

    void GLShader::uploadUniformIntArray(const std::string& name, int* values, uint32_t count) {
        GLint location = glGetUniformLocation(Id, name.c_str());
        glUniform1iv(location, count, values);
    }

    void GLShader::uploadUniformFloat(const std::string& name, float value) const {
        GLint location = glGetUniformLocation(Id, name.c_str());
        glUniform1f(location, value);
    }

    void GLShader::uploadUniformFloat2(const std::string& name, const glm::vec2& value) {
        GLint location = glGetUniformLocation(Id, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void GLShader::uploadUniformFloat3(const std::string& name, const glm::vec3& value) const {
        GLint location = glGetUniformLocation(Id, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void GLShader::uploadUniformFloat4(const std::string& name, const glm::vec4& value) {
        GLint location = glGetUniformLocation(Id, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void GLShader::uploadUniformMat3(const std::string& name, const glm::mat3& matrix) {
        GLint location = glGetUniformLocation(Id, name.c_str());

        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void GLShader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
        GLint location = glGetUniformLocation(Id, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

}; // namespace ChuEngine