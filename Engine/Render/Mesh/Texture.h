#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string_view>
#include "../../Core/Utilities/Logger.h"

// #define STB_IMAGE_STATIC

class CTexture {
public:
    CTexture(std::string filename, GLenum type = GL_TEXTURE_2D);

    inline GLuint GetID() const { return this->m_ID; }

    void Bind(const GLint textureUnit) {
      glActiveTexture(GL_TEXTURE0 + textureUnit);
      glBindTexture(this->m_Type, this->m_ID);
    }

    GLuint GetID() { return this->m_ID; }

    void Unbind() {
      glActiveTexture(0);
      glBindTexture(this->m_Type, 0);
    }

    ~CTexture() {
        glDeleteTextures(1, &this->m_ID);
    }

private:
    GLuint m_ID;
    int m_Width, m_Height;
    unsigned int m_Type;
};

#endif