#version 440

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_texcoord;

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcoord;
out vec3 vs_normal;

uniform mat4 VP; // camera
uniform mat4 ModelMatrix; // transform
  
void main() {
	vs_position = vec4(ModelMatrix * vec4(vertex_position, 1.f)).xyz;
	vs_color = vec3(1.f, 1.f, 1.f);
	vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y * -1.f);
	vs_normal = mat3(ModelMatrix) * vertex_normal;
    gl_Position = VP * vec4(vec3(ModelMatrix * vec4(vertex_position, 1.f)), 1.f);
}