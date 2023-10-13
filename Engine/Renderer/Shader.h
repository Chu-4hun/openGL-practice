//
// Created by Tapok on 09.08.2023.
//
#pragma once

#include <cstdint>
#include <string>

#include "glm/glm.hpp"
namespace ChuEngine {

    class Shader {
      public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void setInt(const std::string& name, int value) = 0;
        virtual void setIntArray(const std::string& name, int* values, uint32_t count) = 0;
        virtual void setFloat(const std::string& name, float value) = 0;
        virtual void setFloat2(const std::string& name, const glm::vec2& value) = 0;
        virtual void setFloat3(const std::string& name, const glm::vec3& value) = 0;
        virtual void setFloat4(const std::string& name, const glm::vec4& value) = 0;
        virtual void setMat4(const std::string& name, const glm::mat4& value) = 0;
    };

} // namespace ChuEngine
