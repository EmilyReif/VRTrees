#version 330 core

in vec3 pos; // world-space position
in vec3 normal;   // world-space normal

layout(location = 0) out vec4 NormalAndDiffuse;
layout(location = 1) out vec4 PosAndSpec;
uniform float colorID;

void main(){
    float spec = 0.2;
    PosAndSpec = vec4(pos, spec);
    float diffuse = colorID;
    NormalAndDiffuse = vec4(normal, diffuse);
}
