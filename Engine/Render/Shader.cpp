#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "../Resources.h"

namespace VK {
    CShader::CShader(bool create) {
        Resources::LoadShader("Default", "Shaders/VertexCore.vs", "Shaders/FragmentCore.vs");
        if (create) {
//            CShader* defaultShader = Resources::LoadShader("Default", "Shaders/VertexCore.vs", "Shaders/FragmentCore.fs");
//            CShader* defaultPbr = Resources::LoadShader("PBR", "Shaders/PBR.vs", "Shaders/PBR.fs");
        }
    }

    CShader::CShader(std::string_view vertexFile, std::string_view fragmentFile, std::string_view geometryFile) {
        this->LoadFromFile(vertexFile.data(), fragmentFile.data());
    }

    GLuint CShader::LoadFromFile(std::string vertex_file_path, std::string fragment_file_path) {
        vertex_file_path = fmt::format("{}{}", RESOURCE_DIR, vertex_file_path);
        fragment_file_path = fmt::format("{}{}", RESOURCE_DIR, fragment_file_path);

        // Create the shaders
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Read the Vertex Shader code from the file
        std::string VertexShaderCode;
        std::ifstream VertexShaderStream(vertex_file_path.c_str(), std::ios::in);
        if(VertexShaderStream.is_open()){
            std::stringstream sstr;
            sstr << VertexShaderStream.rdbuf();
            VertexShaderCode = sstr.str();
            VertexShaderStream.close();
        } else {
            CORE_ERROR("Failed opening shader {}", vertex_file_path);
            return 0;
        }

        // Read the Fragment Shader code from the file
        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream(fragment_file_path.c_str(), std::ios::in);
        if(FragmentShaderStream.is_open()){
            std::stringstream sstr;
            sstr << FragmentShaderStream.rdbuf();
            FragmentShaderCode = sstr.str();
            FragmentShaderStream.close();
        }

        GLint Result = GL_FALSE;
        int InfoLogLength;

        // Compile Vertex Shader
        // CORE_INFO("Compiling Shader: {}", vertex_file_path);
        char const * VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
        glCompileShader(VertexShaderID);

        // Check Vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            CORE_ERROR("{} {}", vertex_file_path, &VertexShaderErrorMessage[0]);
            return -0;
        }

        // Compile Fragment Shader
        char const * FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
        glCompileShader(FragmentShaderID);

        // Check Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            CORE_ERROR("{} {}", fragment_file_path, &FragmentShaderErrorMessage[0]);
            return -1;
        }

        GLuint ProgramID = glCreateProgram();

        // Check the program
        glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            CORE_ERROR("[ID: {}] [VT: {}] [FG: {}]: {}", ProgramID, vertex_file_path, fragment_file_path, &ProgramErrorMessage[0]);
            return -1;
        } else {
            this->LinkProgram(VertexShaderID, FragmentShaderID);
        }

        return ProgramID;
    }

    GLuint CShader::LoadFromFile(GLenum type, std::string filename) {
        filename = fmt::format("{}{}", RESOURCE_DIR, filename.c_str());

        GLuint shader = glCreateShader(type);
        std::string shaderCode;
        std::ifstream VertexShaderStream(filename.data(), std::ios::in);
        if (VertexShaderStream.is_open()){
            std::stringstream sstr;
            sstr << VertexShaderStream.rdbuf();
            shaderCode = sstr.str();
            VertexShaderStream.close();
        } else {
            CORE_ERROR("Failed opening shader {}", filename);
            return 0;
        }

        GLint Result = GL_FALSE;
        int InfoLogLength;
        
        char const * shaderSourcePtr = shaderCode.c_str();
        glShaderSource(shader, 1, &shaderSourcePtr , NULL);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
//            glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            CORE_ERROR("[Type: {}] [File: {}]: {}", type, filename, InfoLogLength);
            return -1;
        }

        return shader;
    }

    void CShader::LinkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader) {
        this->m_ProgramID = glCreateProgram();
        glAttachShader(this->m_ProgramID, vertexShader);
        glAttachShader(this->m_ProgramID, fragmentShader);

        if (geometryShader)
            glAttachShader(this->m_ProgramID, geometryShader);

        glLinkProgram(this->m_ProgramID);

        char infoLog[512];
        GLint success;

        glGetProgramiv(this->m_ProgramID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(this->m_ProgramID, 512, NULL, infoLog);
            CORE_ERROR("Failed linking program: {}", infoLog);
        }

        glUseProgram(0);
    }

    void CShader::Bind() {
        glUseProgram(this->m_ProgramID);
    }

    void CShader::Unbind() {
        glUseProgram(0);
    }

    void CShader::Set1i(GLint value, const GLchar* name) {
        glUniform1i(glGetUniformLocation(this->m_ProgramID, name), value);
    }

    void CShader::Set1f(GLfloat value, const GLchar* name) {
        glUniform1f(glGetUniformLocation(this->m_ProgramID, name), value);
    }

    void CShader::SetVec3f(glm::vec3 value, const GLchar* name) {
        glUniform3fv(glGetUniformLocation(this->m_ProgramID, name), 1, glm::value_ptr(value));
    }

    void CShader::SetVec3f(glm::vec3 value, const std::string& name) {
        glUniform3fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, glm::value_ptr(value));
    }

    void CShader::SetVec4f(glm::vec4 value, const GLchar* name) {
        glUniform4fv(glGetUniformLocation(this->m_ProgramID, name), 1, glm::value_ptr(value));
    }

    void CShader::SetMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose) {
        glUniformMatrix3fv(glGetUniformLocation(this->m_ProgramID, name), 1, transpose, glm::value_ptr(value));
    }

    void CShader::SetMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose) {
        glUniformMatrix4fv(glGetUniformLocation(this->m_ProgramID, name), 1, transpose, glm::value_ptr(value));
    }

    CShader::~CShader() {
        glDeleteProgram(this->m_ProgramID);
    }
}