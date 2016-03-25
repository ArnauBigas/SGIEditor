#version 330 core

uniform sampler2D diffuseBuffer;
uniform sampler2D normalBuffer;
uniform sampler2D depthBuffer;
uniform sampler2D materialBuffer;
uniform sampler2D ssaoTexture;

uniform mat4 invrVP;
uniform float useSsao;
float ambient = 0.25;
int blurSize = 4;

in vec2 uv;
layout(location=0)out vec4 color;

vec3 reconstructPos(vec2 uv_f){
    float z = texture2D(depthBuffer, uv_f).x;
    vec4 sPos = vec4(uv_f * 2.0 - 1.0, z*2.0-1.0, 1.0);
    sPos = invrVP * sPos;

    return (sPos.xyz / sPos.w);
}

float ssao(){
    vec2 texelSize = 1.0 / vec2(textureSize(ssaoTexture, 0));
    float result = 0.0;
    vec2 hlim = vec2(float(-blurSize) * 0.5 + 0.5);
    for (int x = 0; x < blurSize; ++x) {
        for (int y = 0; y < blurSize; ++y) {
            vec2 offset = (hlim + vec2(float(x), float(y))) * texelSize;
            result += texture(ssaoTexture, uv + offset).r;
        }
    }

    return result / float(blurSize * blurSize);
}

void main(){
    if(useSsao > 0.5){
        color = vec4(texture2D(diffuseBuffer, uv).rgb, 1) * ((ambient * ssao()) + texture2D(materialBuffer, uv).b);
    } else {
        color = vec4(texture2D(diffuseBuffer, uv).rgb, 1) * (ambient + texture2D(materialBuffer, uv).b);
    }
}
