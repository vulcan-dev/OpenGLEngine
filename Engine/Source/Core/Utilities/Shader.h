#ifndef SHADER_H
#define SHADER_H

#include "../../RootDir.h.in"
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include "Logger.h"

namespace Shader {
    extern GLuint LoadFromFile(std::string vertex_file_path, std::string fragment_file_path);
}

#endif