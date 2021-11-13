#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include "Vertex.h"
#include "../Shader.h"
#include "Primitive/Primitive.h"
#include <glm/glm.hpp>
#include "../PerspectiveCamera.h"

class CMesh {
public:
    CMesh(const Ref<CMesh>& obj);
    CMesh(Vertex* vertexArray, int type, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices, glm::vec3 position = glm::vec3(0.f), glm::vec3 origin = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
	CMesh(CPrimitive* primitive, int type = GL_TRIANGLES, glm::vec3 position = glm::vec3(0.f), glm::vec3 origin = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));

    void Render(CShader* shader);

	void Move(const glm::vec3& position) {
		this->m_Position += position;
	}

	void Rotate(const glm::vec3& rotation) {
		this->m_Rotation += rotation;
	}

	void SetOrigin(const glm::vec3& origin) {
		this->m_Origin = origin;
	}

    ~CMesh();

private:
    void InitializeVAO();
    void UpdateUniforms(CShader* Shader);
    void UpdateModelMatrix();
	void UpdateViewMatrix(CCamera* camera);

private:
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;

	glm::vec3 m_Position;
	glm::vec3 m_Origin;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
	int m_Type;

	glm::mat4 m_ModelMatrix, m_ViewMatrix;

	Vertex * m_VertexArray;
	GLuint* m_IndexArray;
	int m_TotalVertices;
	int m_TotalIndices;
};

#endif