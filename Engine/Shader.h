#ifndef SHADER_H
#define SHADER_H

#include "RootDir.h.in"
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Core/Utilities/Logger.h"
#include <GL/gl.h>

class CShader {
public:
    CShader(std::string_view vertexFile, std::string_view fragmentFile, std::string_view geometryFile);

    GLuint LoadFromFile(std::string vertex_file_path, std::string fragment_file_path);
    GLuint LoadFromFile(GLenum type, std::string filename);

    ~CShader();

public:
    void LinkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader = -1);

    void Bind();
    void Unbind();

    void Set1i(GLint value, const GLchar* name);

    void SetVec3f(glm::vec3 value, const GLchar* name);
    void SetVec4f(glm::vec4 value, const GLchar* name);

    void SetMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
    void SetMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);

private:
    GLuint m_ProgramID;
};

#endif