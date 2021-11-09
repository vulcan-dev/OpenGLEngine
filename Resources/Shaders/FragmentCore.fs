#version 440

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec3 fs_color;

uniform Material material;
uniform vec3 cameraPos;

void main() {
	fs_color = vec3(texture(material.diffuseTex, vs_texcoord) * vec4(vs_color, 1.f));
}