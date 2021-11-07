#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

out vec3 fragmentColor;
out vec3 vs_position;

uniform mat4 MVP;
uniform mat4 ModelMatrix;
  
void main(){
  vs_position = vec4(ModelMatrix * vec4(vertexPosition_modelspace, 0)).xyz;
  fragmentColor = vertexColor;
  gl_Position = ModelMatrix * vec4(vertexPosition_modelspace, 2);
}