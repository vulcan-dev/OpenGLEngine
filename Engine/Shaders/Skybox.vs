#version 440 core
layout (location = 0) in vec3 vertex_position;

out vec3 TexCoords;

uniform mat4 VP; // camera
uniform mat4 ModelMatrix; // transform

void main() {
    TexCoords = vertex_position;
    gl_Position = VP * vec4(vec3(ModelMatrix * vec4(vertex_position, 1.f)), 1.f);
}