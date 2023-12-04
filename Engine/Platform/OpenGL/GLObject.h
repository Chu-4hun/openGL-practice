//
// Created by Belocurov Dan on 03.12.2023.
//

#pragma once

#include "GLVertex.h"
#include <GL/glew.h>
#include <cstdint>
#include <vector>

namespace ChuEngine {
    struct GlDrawConfig {};

    class GLObject {
      public:
        float scale;
        std::vector<GLVertex> vertices;
        std::vector<uint32_t> indesies;

        GLObject(
            const std::vector<GLVertex>& vertices, const std::vector<uint32_t>& indesies,
            const uint32_t usage_enum
        )
            : scale(1.0f), vertices(vertices), indesies(indesies) {


            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(
                GL_ARRAY_BUFFER, sizeof(GLVertex) * vertices.size(), &vertices[0], usage_enum
            );

            // Coords
            glVertexAttribPointer(
                0, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, coords)
            );
            glEnableVertexAttribArray(0);

            // Color
            glVertexAttribPointer(
                1, 3, GL_FLOAT, true, sizeof(GLVertex), (void*)offsetof(GLVertex, color)
            );
            glEnableVertexAttribArray(1);

            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(
                GL_ELEMENT_ARRAY_BUFFER, indesies.size() * sizeof(uint32_t), indesies.data(),
                usage_enum
            );


            glBindVertexArray(0);
        }
        ~GLObject() {
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            glDeleteVertexArrays(1, &VAO);
        }

        [[nodiscard]] uint32_t getVAO() const { return VAO; }

      private:
        uint32_t VAO;
        uint32_t VBO;
        uint32_t EBO;
        // uint32_t shader;
        // uint32_t texture;
    };

} // namespace ChuEngine
