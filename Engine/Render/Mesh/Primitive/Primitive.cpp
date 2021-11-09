#include "Primitive.h"

void CPrimitive::Set(const Vertex* vertices, const unsigned totalVertices, const GLuint* indices, const unsigned totalIndices) {
    for (size_t i = 0; i < totalVertices; i++) {
        this->m_Vertices.push_back(vertices[i]);
    }

    for (size_t i = 0; i < totalIndices; i++) {
        this->m_Indices.push_back(indices[i]);
    }
}