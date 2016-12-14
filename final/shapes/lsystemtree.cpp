#include "lsystemtree.h"
#include "gl/shaders/ShaderAttribLocations.h"
#include <iostream>
#include <tgmath.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "lsystem/lsystemgenerator.h"
#include <math.h>
using namespace glm;

LSystemTree::LSystemTree(std::map<char, lSystemRule> rules)
    : OpenGLShape(),
    m_cone(),
    m_rulesDict(rules)
{
    setVertexData();
}

LSystemTree:: ~LSystemTree()
{
}

std::vector<float> LSystemTree::makeBranch(int recursionDepth, int heightTesselation, int thetaTesselation, float radius, float height, vec3 angle, float translation) {

    // Generate the verts for the current branch, and return it if we have exceeded maximum recursion depth.
    std::vector<float> verts = m_cone.createVertsVector(heightTesselation, thetaTesselation, radius, height);
    if (recursionDepth < 1) {
        return verts;
    }

    // The smaller the branches get, the less tesselated they are.
    heightTesselation = std::max(1, heightTesselation * 2/3);
    thetaTesselation = std::max(5, thetaTesselation * 2/3);

    // Recursive call to make more branches!
    lSystemRule rule = m_rulesDict['F'];
    std::vector<branch> branches = rule.branches;
    int numBranches = branches.size();

    // Make branches based on the info for the rules, and the current state.
    for (int i = 0; i < numBranches; i++) {
        struct branch bInfo = branches[i];
        vec3 newAngle(rule.angle.x*bInfo.angleXMultiplier, angle.y*bInfo.angleYMultiplier, rule.angle.z*bInfo.angleZMultiplier);
        std::vector<float> b = makeBranch(
                    recursionDepth - 1,
                    heightTesselation,
                    thetaTesselation,
                    std::max(radius * bInfo.scaleRadius, 0.01f),
                    height * bInfo.scaleHeight,
                    newAngle,
                    rule.translationUp *height* bInfo.translationMultiplier);
        verts.insert(verts.end(), b.begin(), b.end());
    }

    // Finally, apply the transform to the entire branch.
    mat4 Transform = mat4();
    vec3 translationTransform = vec3(0.0, translation, 0.0);
    Transform = translate(Transform, translationTransform);
    Transform = rotate(Transform, angle.x, vec3(0, 1, 0));
    Transform = rotate(Transform, angle.y, vec3(1, 0, 0));
    Transform = rotate(Transform, angle.z, vec3(0, 1, 0));
    Transform = translate(Transform, vec3(0, height/2, 0));
    return applyTransformToVerts(verts, Transform);
}

std::vector<float> LSystemTree::applyTransformToVerts(std::vector<float> &verts, mat4 transform) {
    // The transforms to the normals is different than normal points/vectors-- see the lecture.
    mat3 normTransform = inverse(transpose(mat3(transform)));

    // Iterate over the verts and apply the transform!
    for (int i = 0; i < verts.size()/8; i++){
        int idx = i*8;
        vec4 p = vec4(
                    verts[idx + 0],
                    verts[idx + 1],
                    verts[idx + 2], 1);

        vec3 n = vec3(
                verts[idx + 3],
                verts[idx + 4],
                verts[idx + 5]);

        // Position
        vec4 p1 = transform*p;
        verts[idx + 0] = p1[0];
        verts[idx + 1] = p1[1];
        verts[idx + 2] = p1[2];

        // Normal
        vec3 n1 = normalize(normTransform*n);
        verts[idx + 3] = n1[0];
        verts[idx + 4] = n1[1];
        verts[idx + 5] = n1[2];

        // UV
        verts[idx + 6] *= 0.7;
        verts[idx + 7] *= 0.7;
    }
    return verts;
}

void LSystemTree::setVertexData() {
    // Store the vertex data and other values to be used later when constructing the VAO
    int heightTesselation = getParam1() + 1;
    int thetaTesselation = getParam2()+ 2;

    lSystemRule rule = m_rulesDict['F'];
    std::vector<float> verts = makeBranch(rule.maxRecursionLevel,
                                          heightTesselation,
                                          thetaTesselation,
                                          rule.initRadius,
                                          rule.initHeight,
                                          rule.angle,
                                          rule.translationUp);

    // Move the whole thing down so it rotates correctly around the origin
    mat4 Transform = mat4();
    Transform = rotate(Transform, -rule.angle.z, vec3(0, 1, 0));
    Transform = rotate(Transform, -rule.angle.y, vec3(1, 0, 0));
    Transform = rotate(Transform, -rule.angle.x, vec3(0, 1, 0));
    Transform = translate(Transform, vec3(0, -rule.translationUp, 0));
    verts = applyTransformToVerts(verts, Transform);
    OpenGLShape::sendVertexData(verts);
}
