#version 330 core

in vec3 pos; // world-space position
in vec3 normal;   // world-space normal
in float branchIndex;
in float currentBranchIndex;
in float branchPercent;
in vec2 texc;

layout(location = 0) out vec4 NormalAndDiffuse;
layout(location = 1) out vec4 PosAndSpec;




void main(){
    if ((currentBranchIndex < branchIndex)) {
        discard;
    }

    if((currentBranchIndex == branchIndex) && (texc.y > branchPercent)){
        discard;
    }

    float spec = 0.2;
    PosAndSpec = vec4(pos, spec);
    float diffuse = 1.0;
    NormalAndDiffuse = vec4(normal, diffuse);
}
