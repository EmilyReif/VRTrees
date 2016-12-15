#version 330 core

layout(location = 0) in vec3 ObjectSpace_position;
layout(location = 1) in vec3 ObjectSpace_normal;
layout(location = 5) in vec2 texCoord; // UV texture coordinates

uniform mat4 model, view, projection;

out vec3 pos; // world-space position
out vec3 normal;   // world-space normal
out vec2 texc;

void main() {
    texc = texCoord;
    pos =  (model * vec4(ObjectSpace_position, 1.0)).xyz;
    normal = inverse(transpose(mat3(model))) * ObjectSpace_normal;
    pos = pos * 0.5 + 0.5;
    normal = normal * 0.5 + 0.5;
    gl_Position = projection * view * model * vec4(ObjectSpace_position, 1.0);
}
