#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <GL/glew.h>
#include <vector>
#include "Vertex.h"

class CPrimitive {
public:
    CPrimitive() {}

    void Set(const Vertex* vertices, const unsigned totalVertices, const GLuint* indices, const unsigned totalIndices);

	inline Vertex* GetVertices() { return this->m_Vertices.data(); }
	inline GLuint* GetIndices() { return this->m_Indices.data(); }
	inline const int GetTotalVertices() { return this->m_Vertices.size(); }
	inline const int GetTotalIndices() { return this->m_Indices.size(); }

    virtual ~CPrimitive() {}

private:
    std::vector<Vertex> m_Vertices;
    std::vector<GLuint> m_Indices;
};

#endif