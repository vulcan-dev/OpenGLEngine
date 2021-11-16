#version 460 core
layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    vec3 worldPos = vec3(model * vec4(aPos, 0.0));

    gl_Position = projection * view * vec4(worldPos, 1.0);
}