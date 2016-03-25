#version 330 core

uniform sampler2D guiTexture;
uniform vec4 modColor;

in vec2 fragmentUV;

out vec4 color;

void main(){
    color = texture(guiTexture, fragmentUV).rgba * modColor;
}