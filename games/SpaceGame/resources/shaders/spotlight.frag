#version 330 core

uniform sampler2D diffuseBuffer;
uniform sampler2D normalBuffer;
uniform sampler2D depthBuffer;
uniform sampler2D materialBuffer;
uniform sampler2D shadowmapTexture;

uniform mat4 invrVP;
uniform mat4 depthBiasVP;
uniform mat4 Model;

uniform vec3 cameraPosition;

vec3 specular = vec3(1.0, 1.0, 1.0);

in vec2 uv;

out vec4 color;

struct SpotLight {
	vec3 position;	
        vec3 direction;
	vec3 color;	
        float coneAngle;
	float constantAttenuation;
	float linearAttenuation;
	float exponentialAttenuation;
};

uniform SpotLight spotlight;

vec3 reconstructPos(vec2 uv_f){
    float z = texture2D(depthBuffer, uv_f).x;
    vec4 sPos = vec4(uv_f * 2.0 - 1.0, z*2.0-1.0, 1.0);
    sPos = invrVP * sPos;

    return (sPos.xyz / sPos.w);
}

vec4 calcSpotLightColor(vec3 fragPos, vec3 fragmentNormal, float specular, float shininess){
    vec4 shadowCoord = depthBiasVP * vec4(fragPos, 1);
    shadowCoord /= shadowCoord.w;
    if ( texture2D( shadowmapTexture, shadowCoord.xy ).r  <  shadowCoord.z-0.0001){
        return vec4(0, 0, 0, 1);
    } else {
        vec3 dir = spotlight.position - fragPos;
        float dist = length(dir);
        float NdotL = max(dot(fragmentNormal, normalize(dir)),0.0);
        if (NdotL > 0.0) {     
            float spotEffect = max(dot(normalize(spotlight.direction), normalize(-dir)), 0.0);
            if (spotEffect > spotlight.coneAngle) {
                float att = spotEffect / (spotlight.constantAttenuation + spotlight.linearAttenuation * dist + spotlight.exponentialAttenuation * dist * dist);
                return vec4(spotlight.color*att * NdotL, 1.0) + vec4(spotlight.color * specular * pow(max(dot(normalize(reflect(spotlight.position - fragPos, fragmentNormal)), normalize(fragPos - cameraPosition)), 0.0), shininess), 1.0);
            }
        }
    }
}

void main(){
    color = vec4(texture2D(diffuseBuffer, uv).rgb, 1) * (calcSpotLightColor(reconstructPos(uv), texture2D(normalBuffer, uv).rgb, texture2D(materialBuffer, uv).g, texture2D(materialBuffer, uv).r));
}
