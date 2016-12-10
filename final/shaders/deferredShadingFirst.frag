#version 330 core

in vec3 pos; // world-space position
in vec3 normal;   // world-space normal
in vec2 texc;
uniform sampler2D tex;

layout(location = 0) out vec4 NormalAndDiffuse;
layout(location = 1) out vec4 PosAndSpec;
layout(location = 2) out vec4 Color;

void main(){
    vec4 c = texture(tex, texc);
    Color = vec4(0.8, 0.5, 0.4, 1.0)* c;
    float spec = Color.x;
    PosAndSpec = vec4(pos, spec);
    float diffuse = 1.0;
    NormalAndDiffuse = vec4(normal, diffuse);
    NormalAndDiffuse.x += c.r;
    NormalAndDiffuse.y += c.g;
    NormalAndDiffuse.z += c.b;

}
