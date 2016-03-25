#version 330 core

uniform sampler2D diffuseTexture;

uniform vec4 matDiffuse;
uniform vec4 specular;
uniform vec4 matEmission;

uniform float shininess;

in vec2 fragmentUV;
in vec3 fragmentNormal;

layout(location=0)out vec4 color;
layout(location=1)out vec4 normal;
layout(location=2)out vec4 material;

void main(){
    color = vec4(texture(diffuseTexture, fragmentUV).rgb * matDiffuse.rgb, 1.0);
    normal = vec4(fragmentNormal, 1.0);
    material = vec4(shininess, specular.r, matEmission.r, 1.0);
}
