#pragma once

#include "RootDir.h.in"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Core/Utilities/Logger.h"
#include "Core/Input.h"
#include "Core/Window.h"

#include "Render/Camera.h"
#include "Render/Shader.h"
#include "Render/Skybox.h"

#include "Render/Mesh/Mesh.h"
#include "Render/Mesh/Texture.h"
#include "Render/Mesh/Model.h"
#include "Render/Mesh/Primitive/Cube.h"
#include "Render/Mesh/Primitive/Sphere.h"

template<typename T>
using Ref = std::shared_ptr<T>;