#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string_view>
#include "../Core/Utilities/Logger.h"
#include "../Core/stb_image.h"

class CTexture {
public:
    CTexture(std::string filename, GLenum type) {
        filename = fmt::format("..{}/{}", ROOT_DIR, filename.c_str());
        this->m_Type = type;

        int cp;

        // unsigned char* image = SOIL_load_image(filename.data(), &this->m_Width, &this->m_Height, nullptr, SOIL_LOAD_RGBA);
        unsigned char* image = stbi_load(filename.c_str(), &this->m_Width, &this->m_Height, &cp, 4);

        glGenTextures(1, &this->m_ID);
        glBindTexture(type, this->m_ID);

        glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        if (image) {
            glTexImage2D(type, 0, GL_RGBA, this->m_Width, this->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(type);
        } else {
            CORE_ERROR("Failed loading texture: {}", filename.c_str());
        }

        glActiveTexture(0);
        glBindTexture(type, 0);
        stbi_image_free(image);
    }

    inline GLuint GetID() const { return this->m_ID; }

    void Bind(const GLint textureUnit) {
      glActiveTexture(GL_TEXTURE0 + textureUnit);
      glBindTexture(this->m_Type, this->m_ID);
    }

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