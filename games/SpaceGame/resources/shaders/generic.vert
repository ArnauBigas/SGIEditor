#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;

out vec2 fragmentUV;
out vec3 fragmentNormal;

uniform mat4 MVP;
uniform mat4 Model;

void main(){
    gl_Position = MVP * vec4(vertexPosition_modelspace,1);
    fragmentUV = vertexUV;
    fragmentNormal = vec3(Model * vec4(vertexNormal, 0));
}