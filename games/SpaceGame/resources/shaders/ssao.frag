#version 330 core

uniform sampler2D normalBuffer;
uniform sampler2D depthBuffer;
uniform sampler2D noiseTexture;

uniform vec2 noiseScale;
uniform int kernelSize;
uniform vec3[16] kernel;

uniform mat4 invrVP;
uniform mat4 MVP;

float radius = 0.5;
float power = 0.2;

in vec2 uv;
layout(location=0)out vec4 ssao;

vec3 reconstructPos(vec2 uv_f){
    float z = texture2D(depthBuffer, uv_f).x;
    vec4 sPos = vec4(uv_f * 2.0 - 1.0, z*2.0-1.0, 1.0);
    sPos = invrVP * sPos;

    return (sPos.xyz / sPos.w);
}

void main(){
    vec3 normal = texture2D(normalBuffer, uv).rgb;
    vec3 rvec = texture2D(noiseTexture, uv * noiseScale).rgb * 2.0 - 1.0;
    vec3 tangent = normalize(rvec - normal * dot(rvec, normal));
    vec3 bitangent = cross(tangent, normal);
    mat3 kernelBasis = mat3(tangent, bitangent, normal);
    vec3 originPos = reconstructPos(uv);
    float originDepth = texture2D(depthBuffer, uv).x;
    float occlusion = 0.0;
    for (int i = 0; i < kernelSize; ++i) {
        //get sample position:
        vec3 samplePos = kernelBasis * kernel[i];
        samplePos = samplePos * radius + originPos;

        //project sample position:
        vec4 offset = MVP * vec4(samplePos, 1.0);
        offset.xy /= offset.w; // only need xy
        offset.xy = offset.xy * 0.5 + 0.5; // scale/bias to texcoords


        //get sample depth:
        float sampleDepth = texture2D(depthBuffer, offset.xy).x;

        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(originDepth - sampleDepth));
        occlusion += rangeCheck * step(originDepth, sampleDepth);

    }

    occlusion = occlusion / float(kernelSize);
    ssao = vec4(pow(occlusion, power));
}
