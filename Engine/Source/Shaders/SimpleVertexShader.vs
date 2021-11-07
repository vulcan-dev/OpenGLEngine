#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

out vec3 fragmentColor;
out vec3 vs_position;

uniform mat4 VP; // camera
uniform mat4 ModelMatrix; // transform
  
void main(){
    fragmentColor = vertexColor;
    gl_Position = VP * vec4(vec3(ModelMatrix * vec4(vertexPosition_modelspace, 1.f)), 1.f);
}