#version 330 core

layout(location = 0) in vec3 ObjectSpace_position;
layout(location = 1) in vec3 ObjectSpace_normal;
layout(location = 5) in vec2 texCoord; // UV texture coordinates
layout(location = 6) in float branch;

uniform mat4 model, view, projection;
uniform float currentBranch;
uniform float percent;

out vec3 pos; // world-space position
out vec3 normal;   // world-space normal
out vec2 texc;
out float branchIndex;
out float currentBranchIndex;
out float branchPercent;

void main() {
    texc = texCoord;
    branchIndex = branch;
    currentBranchIndex = currentBranch;
    branchPercent = percent;
    pos =  (model * vec4(ObjectSpace_position, 1.0)).xyz;
    normal = inverse(transpose(mat3(model))) * ObjectSpace_normal;
    normal = normal * 0.5 + 0.5;
    gl_Position = projection * view * model * vec4(ObjectSpace_position, 1.0);
}
