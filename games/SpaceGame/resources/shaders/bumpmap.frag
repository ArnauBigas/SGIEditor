#version 330 core

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;

uniform vec4 matDiffuse;
uniform vec4 specular;
uniform vec4 matEmission;
uniform mat4 Model;
uniform float shininess;

in vec2 fragmentUV;
in vec3 fragmentNormal;

layout(location=0)out vec4 color;
layout(location=1)out vec4 normal;
layout(location=2)out vec4 material;

void main(){
    color = vec4(texture2D(diffuseTexture, fragmentUV).rgb * matDiffuse.rgb, 1.0);
    mat3 normalMat = mat3(Model);
    vec3 tangent = normalize(normalMat[0]); 
    vec3 binormal = normalize(normalMat[1]);
    mat3 tangentToWorld = mat3(tangent.x, binormal.x, fragmentNormal.x,
                               tangent.y, binormal.y, fragmentNormal.y,
                               tangent.z, binormal.z, fragmentNormal.z);
    normal = vec4(((texture2D(normalTexture, fragmentUV).rgb * 2.0 - 1.0) * tangentToWorld), 1.0);
    material = vec4(shininess, specular.r, matEmission.r, 1.0);
}