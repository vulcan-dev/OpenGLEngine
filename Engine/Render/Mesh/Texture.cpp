#include "Texture.h"

#include "../../RootDir.h.in"

// #define STB_IMAGE_IMPLEMENTATION
// #include "../../ThirdParty/stb_image.h"

CTexture::CTexture(std::string filename, GLenum type) {
    // filename = fmt::format("..{}/{}", ROOT_DIR, filename.c_str());
    // this->m_Type = type;

    // int component;
    // stbi_set_flip_vertically_on_load(true);
    // unsigned char* image = stbi_load(filename.c_str(), &this->m_Width, &this->m_Height, &component, 4);

    // glGenTextures(1, &this->m_ID);
    // glBindTexture(type, this->m_ID);

    // // glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // // glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // // glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // // glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // if (image) {
    //     glTexImage2D(type, 0, GL_RGB16F, this->m_Width, this->m_Height, 0, GL_RGB, GL_FLOAT, image); // CHANGE GL_RGB16F to GL_RGBA
    //     // glGenerateMipmap(type);
    // } else {
    //     CORE_ERROR("Failed loading texture: {}", filename.c_str());
    // }

    // glActiveTexture(0);
    // glBindTexture(type, 0);
    // stbi_image_free(image);
}