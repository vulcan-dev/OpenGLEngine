#ifndef INCLUDE_H
#define INCLUDE_H

#include "RootDir.h.in"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Core/Utilities/Logger.h"
#include "Core/Input.h"

#include "Render/PerspectiveCamera.h"
#include "Render/Shader.h"

#include "Render/Mesh/Model.h"
#include "Render/Mesh/Mesh.h"
#include "Render/Mesh/Vertex.h"
#include "Render/Mesh/Primitive/Cube.h"

template<typename T>
using Ref = std::shared_ptr<T>;

#endif