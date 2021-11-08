#ifndef PRIMITIVECUBE_H
#define PRIMITIVECUBE_H

#include "Primitive.h"

class CPrimitiveCube : public CPrimitive {
public:
    CPrimitiveCube() : CPrimitive() {
    Vertex vertices[] = {
        // side 1
        glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

        glm::vec3(1.0f, 1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, -1.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f, 1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(-1.f, -1.f),		glm::vec3(0.f, 0.f, 1.f),

        // side 2
        glm::vec3(1.0f,-1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(1.0f,-1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

        glm::vec3(1.0f, 1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(1.0f,-1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, -1.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(-1.f, -1.f),		glm::vec3(0.f, 0.f, 1.f),

        // side 3
        glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f, 1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

        glm::vec3(1.0f,-1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, -1.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(-1.f, -1.f),		glm::vec3(0.f, 0.f, 1.f),

        // side 4
        glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(1.0f,-1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(1.0f,-1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, -1.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(1.0f, 1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(-1.f, -1.f),		glm::vec3(0.f, 0.f, 1.f),

        // side 5
        glm::vec3(1.0f,-1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(1.0f,-1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(1.0f, 1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, -1.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f, 1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(-1.f, -1.f),		glm::vec3(0.f, 0.f, 1.f),

        // side 6
        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f, 1.0f,-1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, -1.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(1.0f,-1.0f, 1.0f), glm::vec3(1.f, 0.f, 0.f),		glm::vec2(-1.f, -1.f),		glm::vec3(0.f, 0.f, 1.f),
    };
    GLuint indices[] = {
        // 1
        0, 1, 2,
        3, 4, 5,

        // 2
        6, 7, 8,
        9, 10, 11,
        
        // 3
        12, 13, 14,
        15, 16, 17,

        // 4
        18, 19, 20,
        21, 22, 23,

        // 5
        24, 25, 26,
        27, 28, 29,

        // 6
        30, 31, 32,
        33, 34, 35
    };

		// Vertex vertices[] = {
		// 	//Position								//Color							//Texcoords					//Normals
		// 	glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
		// 	glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		// 	glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		// 	glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

		// 	glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
		// 	glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
		// 	glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
		// 	glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f)
		// };

        unsigned totalVertices = sizeof(vertices) / sizeof(Vertex);

		// GLuint indices[] = {
		// 	0, 1, 2,
		// 	0, 2, 3,

		// 	7, 6, 1,
		// 	7, 1, 0,

		// 	4, 5, 6,
		// 	4, 6, 7,

		// 	3, 2, 5,
		// 	3, 5, 4
		// };

		unsigned totalIndices = sizeof(indices) / sizeof(GLuint);

		this->Set(vertices, totalVertices, indices, totalIndices);
    }
};

#endif