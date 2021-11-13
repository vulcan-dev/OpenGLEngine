#include "Primitive.h"

#include "../../../Core/Utilities/Logger.h"
#include <glm/gtx/string_cast.hpp>

void CPrimitive::Set(const Vertex* vertices, const unsigned totalVertices, const GLuint* indices, const unsigned totalIndices) {
    for (size_t i = 0; i < totalVertices; i++) {
        this->m_Vertices.push_back(vertices[i]);
    }

    for (size_t i = 0; i < totalIndices; i++) {
        this->m_Indices.push_back(indices[i]);
    }
}

void CPrimitive::Set2(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> uv, std::vector<unsigned int> indices) {
    std::vector<Vertex> data;

    this->m_Indices = indices;

    for (size_t i = 0; i < positions.size(); i++) {
        this->m_Vertices.push_back((Vertex)positions[i]);
    }

    for (size_t i = 0; i < normals.size(); i++) {
        m_Vertices[i].normal = normals[i];
    }

    for (size_t i = 0; i < uv.size(); i++) {
        m_Vertices[i].texcoord = uv[i];
    }
}