#version 330 core

in vec3 pos; // world-space position
in vec3 normal;   // world-space normal
in vec2 texc;
uniform sampler2D tex;

layout(location = 0) out vec4 NormalAndDiffuse;
layout(location = 1) out vec4 PosAndSpec;

void main(){
    vec4 c = texture(tex, texc);
    float spec = 1;
    PosAndSpec = vec4(pos, spec);
    float diffuse = 1.0;
    NormalAndDiffuse = vec4(normal, diffuse);
//    NormalAndDiffuse.x += c.r;
//    NormalAndDiffuse.y += c.r;
//    NormalAndDiffuse.z += c.r;

}
