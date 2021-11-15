#include "Mesh.h"

#include <glm/gtc/matrix_transform.hpp>

namespace VK {
    CMesh::CMesh(Vertex* vertexArray, int type, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices, glm::vec3 position, glm::vec3 origin, glm::vec3 rotation, glm::vec3 scale) {
        this->m_Position = position;
        this->m_Origin = origin;
        this->m_Rotation = rotation;
        this->m_Scale = scale;
        this->m_Type = type;

        this->m_TotalVertices = nrOfVertices;
        this->m_TotalIndices = nrOfIndices;

        this->m_VertexArray = new Vertex[this->m_TotalVertices];
        for (int i = 0; i < this->m_TotalVertices; i++) {
            this->m_VertexArray[i] = vertexArray[i];
        }

        this->m_IndexArray = new GLuint[this->m_TotalIndices];
        for (int i = 0; i < this->m_TotalIndices; i++) {
            this->m_IndexArray[i] = indexArray[i];
        }

        this->InitializeVAO();
        this->UpdateModelMatrix();
    }

    CMesh::CMesh(const Ref<CMesh>& obj) {
        this->m_Position = obj->m_Position;
        this->m_Origin = obj->m_Origin;
        this->m_Rotation = obj->m_Rotation;
        this->m_Scale = obj->m_Scale;
        this->m_Type = obj->m_Type;

        this->m_TotalVertices = obj->m_TotalVertices;
        this->m_TotalIndices = obj->m_TotalIndices;

        this->m_VertexArray = new Vertex[this->m_TotalVertices];
        for (auto i = 0; i < this->m_TotalVertices; i++) {
            this->m_VertexArray[i] = obj->m_VertexArray[i];
        }

        this->m_IndexArray = new GLuint[this->m_TotalIndices];
        for (auto i = 0; i < this->m_TotalIndices; i++) {
            this->m_IndexArray[i] = obj->m_IndexArray[i];
        }

        this->InitializeVAO();
        this->UpdateModelMatrix();
    }

    CMesh::CMesh(CPrimitive* primitive, int type, glm::vec3 position, glm::vec3 origin, glm::vec3 rotation, glm::vec3 scale) {
        this->m_Position = position;
        this->m_Origin = origin;
        this->m_Rotation = rotation;
        this->m_Scale = scale;
        this->m_Type = type;

        this->m_TotalVertices = primitive->GetTotalVertices();
        this->m_TotalIndices = primitive->GetTotalIndices();

        this->m_VertexArray = new Vertex[this->m_TotalVertices];
        for (int i = 0; i < this->m_TotalVertices; i++) {
            this->m_VertexArray[i] = primitive->GetVertices()[i];
        }

        this->m_IndexArray = new GLuint[this->m_TotalIndices];
        for (int i = 0; i < this->m_TotalIndices; i++) {
            this->m_IndexArray[i] = primitive->GetIndices()[i];
        }

        this->InitializeVAO();
        this->UpdateModelMatrix();
    }

    void CMesh::InitializeVAO() {
        glCreateVertexArrays(1, &this->m_VAO);
        glGenBuffers(1, &this->m_VBO);

        glBindVertexArray(this->m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
        glBufferData(GL_ARRAY_BUFFER, this->m_TotalVertices * sizeof(Vertex), this->m_VertexArray, GL_STATIC_DRAW);

        if (this->m_TotalIndices > 0) {
            glGenBuffers(1, &this->m_EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_TotalIndices * sizeof(GLuint), this->m_IndexArray, GL_STATIC_DRAW);
        }

        unsigned int stride = (3 + 2 + 3) * sizeof(float);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));

        glBindVertexArray(0);
    }

    void CMesh::UpdateUniforms(CShader* shader) {
        shader->SetMat4fv(this->m_ModelMatrix, "model");
    }

    void CMesh::UpdateModelMatrix() {
        this->m_ModelMatrix = glm::mat4(1.f);
        this->m_ModelMatrix = glm::translate(this->m_ModelMatrix, this->m_Origin);
        this->m_ModelMatrix = glm::rotate(this->m_ModelMatrix, glm::radians(this->m_Rotation.x), glm::vec3(1.f, 0.f, 0.f));
        this->m_ModelMatrix = glm::rotate(this->m_ModelMatrix, glm::radians(this->m_Rotation.y), glm::vec3(0.f, 1.f, 0.f));
        this->m_ModelMatrix = glm::rotate(this->m_ModelMatrix, glm::radians(this->m_Rotation.z), glm::vec3(0.f, 0.f, 1.f));
        this->m_ModelMatrix = glm::translate(this->m_ModelMatrix, this->m_Position - this->m_Origin);
        this->m_ModelMatrix = glm::scale(this->m_ModelMatrix, this->m_Scale);
    }

    void CMesh::Render(CShader* shader) {
        this->UpdateModelMatrix();
        this->UpdateUniforms(shader);

        // shader->Set1i(0, "irradianceMap");
        // shader->Set1i(1, "prefilterMap");
        // shader->Set1i(2, "brdfLUT");
        // shader->SetVec3f(glm::vec3(.5f, .5f, .5f), "albedo");
        // shader->Set1f(1.f, "ao");

        glBindVertexArray(this->m_VAO);

        if (this->m_TotalIndices > 0) {
            glDrawElements(this->m_Type, this->m_TotalIndices, GL_UNSIGNED_INT, 0);
        } else {
            glDrawArrays(this->m_Type, 0, this->m_TotalVertices);
        }
    }

    CMesh::~CMesh() {
        glDeleteVertexArrays(1, &this->m_VAO);
        glDeleteBuffers(1, &this->m_VBO);

        if (this->m_TotalIndices > 0) {
            glDeleteBuffers(1, &this->m_EBO);
        }

        delete[] this->m_VertexArray;
        delete[] this->m_IndexArray;
    }
}