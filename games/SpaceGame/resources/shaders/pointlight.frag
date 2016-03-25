#version 330 core

uniform sampler2D diffuseBuffer;
uniform sampler2D normalBuffer;
uniform sampler2D depthBuffer;
uniform sampler2D materialBuffer;

uniform mat4 invrVP;

uniform vec3 cameraPosition;

vec3 specular = vec3(1.0, 1.0, 1.0);

in vec2 uv;

out vec4 color;

struct PointLight {
	vec3 position;	
	vec3 color;	
	float constantAttenuation;
	float linearAttenuation;
	float exponentialAttenuation;
};

uniform PointLight pointlight;

vec3 reconstructPos(vec2 uv_f){
    float z = texture2D(depthBuffer, uv_f).x;
    vec4 sPos = vec4(uv_f * 2.0 - 1.0, z*2.0-1.0, 1.0);
    sPos = invrVP * sPos;

    return (sPos.xyz / sPos.w);
}

vec4 calcPointLightColor(vec3 fragPos, vec3 fragmentNormal, float specular, float shininess){
    float dist = length(pointlight.position - fragPos);
    float fDiffuse = dot(fragmentNormal, pointlight.position - fragPos) / dist; 		
    fDiffuse = clamp(fDiffuse, 0, 1);
    float att = pointlight.constantAttenuation + pointlight.linearAttenuation * dist + pointlight.exponentialAttenuation * dist * dist;
    return vec4(pointlight.color*(fDiffuse/att) + pointlight.color * specular * pow(max(dot(normalize(reflect(pointlight.position - fragPos, fragmentNormal)), normalize(fragPos - cameraPosition)), 0.0), shininess), 1.0); 
}

void main(){
    vec2 mat = texture2D(materialBuffer, uv).rg;
    color = vec4(texture2D(diffuseBuffer, uv).rgb, 1) * (calcPointLightColor(reconstructPos(uv), texture2D(normalBuffer, uv).rgb, mat.g, mat.r));
}
