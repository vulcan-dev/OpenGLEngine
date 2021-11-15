#pragma once

#include "Primitive.h"

namespace VK {
    class CPrimitiveCube : public CPrimitive {
    public:
        CPrimitiveCube() : CPrimitive() {
            Vertex vertices[] = {
                // back face
                glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 0.0f),
                glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 1.0f),
                glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 0.0f),
                glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 1.0f),
                glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 0.0f),
                glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 1.0f),
                // front face
                glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 0.0f),
                glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 0.0f),
                glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 1.0f),
                glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 1.0f),
                glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 1.0f),
                glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 0.0f),
                // left face
                glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(-1.0f, 0.0f,  0.0f), glm::vec2(1.0f, 0.0f),
                glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(-1.0f, 0.0f,  0.0f), glm::vec2(1.0f, 1.0f),
                glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 0.0f,  0.0f), glm::vec2(0.0f, 1.0f),
                glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 0.0f,  0.0f), glm::vec2(0.0f, 1.0f),
                glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(-1.0f, 0.0f,  0.0f), glm::vec2(0.0f, 0.0f),
                glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(-1.0f, 0.0f,  0.0f), glm::vec2(1.0f, 0.0f),

                // right face
                glm::vec3(1.0f,  1.0f,  1.0f),  glm::vec3(1.0f, 0.0f,  0.0f), glm::vec2(1.0f, 0.0f),
                glm::vec3(1.0f, -1.0f, -1.0f),  glm::vec3(1.0f, 0.0f,  0.0f), glm::vec2(0.0f, 1.0f),
                glm::vec3(1.0f,  1.0f, -1.0f),  glm::vec3(1.0f, 0.0f,  0.0f), glm::vec2(1.0f, 1.0f),
                glm::vec3(1.0f, -1.0f, -1.0f),  glm::vec3(1.0f, 0.0f,  0.0f), glm::vec2(0.0f, 1.0f),
                glm::vec3(1.0f,  1.0f,  1.0f),  glm::vec3(1.0f, 0.0f,  0.0f), glm::vec2(1.0f, 0.0f),
                glm::vec3(1.0f, -1.0f,  1.0f),  glm::vec3(1.0f, 0.0f,  0.0f), glm::vec2(0.0f, 0.0f),

                // bottom face
                glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f),
                glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 1.0f),
                glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f),
                glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f),
                glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 0.0f),
                glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f),

                // top face
                glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f), glm::vec2(0.0f, 1.0f),
                glm::vec3( 1.0f,  1.0f , 1.0f), glm::vec3(0.0f, 1.0f,  0.0f), glm::vec2(1.0f, 0.0f),
                glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f), glm::vec2(1.0f, 1.0f),
                glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f,  0.0f), glm::vec2(1.0f, 0.0f),
                glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f), glm::vec2(0.0f, 1.0f),
                glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f,  0.0f), glm::vec2(0.0f, 0.0f),
            };

            unsigned totalVertices = sizeof(vertices) / sizeof(Vertex);

            this->Set(vertices, totalVertices, 0, 0);
        }
    };
}