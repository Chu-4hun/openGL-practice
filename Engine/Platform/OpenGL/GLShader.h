//
// Created by Belocurov Dan on 10.08.2023.
//
#pragma once

#include "Renderer/Shader.h"
#include <cstdint>
#include <string>


namespace ChuEngine {
    struct ShaderSources {
        std::string vertexSource;
        std::string fragmentSource;
    };

    class GLShader : Shader {
      public:
        explicit GLShader(const std::string& filepath);
        GLShader(std::string name, const std::string& vertexSrc, const std::string& fragmentSrc);
        ~GLShader() override;

        void bind() const override;
        void unbind() const override;

        virtual void setInt(const std::string& name, int value) override;
	virtual void setIntArray(const std::string& name, int* values, uint32_t count) override;
	virtual void setFloat(const std::string& name, float value) override;
	virtual void setFloat2(const std::string& name, const glm::vec2& value) override;
	virtual void setFloat3(const std::string& name, const glm::vec3& value) override;
	virtual void setFloat4(const std::string& name, const glm::vec4& value) override;
	virtual void setMat4(const std::string& name, const glm::mat4& value) override;

        [[nodiscard]] uint32_t getId() const { return Id; }

      protected:
        void uploadUniformInt(const std::string& name, int value);
        void uploadUniformIntArray(const std::string& name, int* values, uint32_t count);
        void uploadUniformFloat2(const std::string& name, const glm::vec2& value);
        void uploadUniformFloat4(const std::string& name, const glm::vec4& value);
        void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
        void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);
        void uploadUniformFloat3(const std::string& name, const glm::vec3& value) const;
        void uploadUniformFloat(const std::string& name, float value) const;
      private:
        uint32_t Id;
        const std::string Name;

        static ShaderSources parseShader(const std::string& path);
        static unsigned int compileShader(const std::string& source, unsigned int shaderType);

    };

} // namespace ChuEngine
