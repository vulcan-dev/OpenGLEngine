#version 440 core

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_texcoord;
layout (location = 2) in vec3 vertex_normal;

out vec3 vs_position;
out vec2 vs_texcoord;
out vec3 vs_cameraPos;
out vec3 vs_normal;

uniform vec2 UV;

uniform mat4 ProjectionMatrix; // camera
uniform vec3 CameraPosition;
uniform mat4 ModelMatrix; // transform

void main(){
	gl_Position = ProjectionMatrix * ModelMatrix * vec4(vertex_position, 1.0);
	vec4 vertPos4 = ModelMatrix * vec4(vertex_position, 1.0);

	vs_position = vec3(vertPos4) / vertPos4.w;
	vs_cameraPos = vertex_position - CameraPosition;
	vs_normal = vertex_normal;

	vs_texcoord = UV;

	// vs_position = vec4(ModelMatrix * vec4(vertex_position, 1.f)).xyz;
	// vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y * -1.f);
	// vs_normal = mat3(ModelMatrix) * vertex_normal;
}