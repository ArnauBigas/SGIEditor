#version 330 core

vec2 quadVertices[4] = vec2[](vec2(-1.0, -1.0), vec2(1.0, -1.0), vec2(-1.0, 1.0), vec2(1.0, 1.0));

out vec2 uv;

void main()
{
    gl_Position = vec4(quadVertices[gl_VertexID], 0.0, 1.0);
    uv = (quadVertices[gl_VertexID]+1.0)/2.0;
}