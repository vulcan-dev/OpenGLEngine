#pragma once

#include "Render/Shader.h"
#include "Render/Mesh/Texture.h"
#include "Render/Mesh/Material.h"
#include "Render/Mesh/Mesh.h"

#include <map>

namespace VK {
    class Resources {
    public:
        static void Initialize();
        static void Clean();

    public:
        static CShader* LoadShader(std::string_view string_view, std::string_view vsPath, std::string_view fsPath);
        static CShader* GetShader(std::string_view name);

        static CTexture* LoadTexture(std::string_view name, std::string_view path, GLenum target, bool srgb);
        static CTexture* GetTexture(std::string_view name);

        static CMaterial* LoadMaterial(std::string_view name, std::string_view path);
        static CMaterial* GetMaterial(std::string_view name);

        static CMesh* LoadMesh(std::string_view name, GLuint vertices, GLuint indices);
        static CMesh* GetMesh(std::string_view name);

    private:
        static std::map<unsigned int, CShader> m_Shaders;
        static std::map<unsigned int, CTexture> m_Textures;
        static std::map<unsigned int, CMaterial> m_Materials;
        static std::map<unsigned int, CMesh> m_Meshes;
    };
}