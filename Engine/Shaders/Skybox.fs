// #version 440 core
// out vec4 FragColor;

// in vec3 vs_texcoords;

// uniform samplerCube skybox;

// void main() { 
//     FragColor = texture(skybox, vs_texcoords);
// }

// new
#version 440 core

struct Material
{
	float bNormal;

	sampler2D normal;
	sampler2D tEquirect;
};

in vec3 vs_normal;
in vec3 vs_position;
in vec2 vs_texcoord;

in vec3 vs_cameraPos;
uniform Material material;

out vec4 fs_color;

#define RECIPROCAL_PI2 0.15915494
#define saturate(a) clamp( a, 0.0, 1.0 )

// Per-Pixel Tangent Space Normal Mapping
// http://hacksoflife.blogspot.ch/2009/11/per-pixel-tangent-space-normal-mapping.html
vec3 perturbNormal( vec3 eye_pos, vec3 surf_norm, vec2 uv_coords, vec3 normal_perturbation ) {
	vec3 q0 = dFdx( eye_pos.xyz );
	vec3 q1 = dFdy( eye_pos.xyz );
	vec2 st0 = dFdx( uv_coords.st );
	vec2 st1 = dFdy( uv_coords.st );

	vec3 S = normalize( q0 * st1.t - q1 * st0.t );
	vec3 T = normalize( -q0 * st1.s + q1 * st0.s );
	vec3 N = normalize( surf_norm );

	mat3 tsn = mat3( S, T, N );
	return normalize( tsn * normal_perturbation );
}

void main() {
	vec3 mapN = texture2D( material.normal, vs_texcoord ).xyz * 2.0 - 1.0;
	mapN = mix(mapN, vec3(0,0,1), 0.8);
	vec3 normal = normalize(vs_normal);

	normal = mix(normal, perturbNormal(vs_position, normal, vs_texcoord, mapN), material.bNormal);

	vec3 reflectVec = normalize(reflect(vs_cameraPos, normal));
	vec2 uv;
	uv.y = saturate( reflectVec.y * 0.5 + 0.5 );
	uv.x = atan( -reflectVec.z, -reflectVec.x ) * RECIPROCAL_PI2 + 0.5;
	fs_color = texture2D( material.tEquirect, uv );
	// fs_color = vec3(texture(material.diffuseTex, vs_texcoord));
}