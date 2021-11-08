#version 330 core
layout (location = 0) in vec3 vertexPosition_modelspace;

out vec3 TexCoords;

uniform mat4 VP; // camera
uniform mat4 ModelMatrix; // transform

void main() {
    TexCoords = vertexPosition_modelspace;
    gl_Position = VP * vec4(vec3(ModelMatrix * vec4(vertexPosition_modelspace, 1.f)), 1.f);
}