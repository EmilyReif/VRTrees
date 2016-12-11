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

std::vector<float> LSystemTree::makeBranch(int recursionDepth, int heightTesselation, int thetaTesselation, float radius, float height, vec3 scale, float angleX, float angleZ, float translation) {
    std::vector<float> verts = m_cone.createVertsVector(heightTesselation, thetaTesselation, radius, height);
    if (recursionDepth < 1) {
        return verts;
    }

    // The smaller the branches get, the less tesselated they are
    heightTesselation = std::max(1, heightTesselation * 2/3);
    thetaTesselation = std::max(3, thetaTesselation * 2/3);

    // Also, the radius decreases.
    float newRad = std::max(radius * scale.x, 0.07f);

    // Recursive call to make more branches!
    lSystemRule rule = m_rulesDict['F'];
    std::vector<branch> branches = rule.branches;
    int numBranches = branches.size();

    // Make branches based on the info for the rules, and the current state.
    for (int i = 0; i < numBranches; i++) {
        struct branch bInfo = branches[i];
        std::vector<float> b = makeBranch(
                    recursionDepth - 1,
                    heightTesselation,
                    thetaTesselation,
                    newRad,
                    height,
                    bInfo.scale,
                    angleX * bInfo.angleXMultiplier,
                    angleZ * bInfo.angleZMultiplier,
                    rule.translationUp * bInfo.translationMultiplier);
        verts.insert(verts.end(), b.begin(), b.end());
    }

    // FACK
    mat4 Transform = mat4();
    vec3 translationTransform = vec3(0.0, translation, 0.0);
    Transform = translate(Transform, translationTransform);
    Transform = glm::scale(Transform, scale);
    Transform = rotate(Transform, angleX, vec3(0, 0, 1));
    Transform = rotate(Transform, angleZ, vec3(1, 0, 0));

    Transform = translate(Transform, vec3(0, height/2, 0));


    mat3 normTransform = inverse(transpose(mat3(Transform)));

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
        vec4 p1 = Transform*p;
        verts[idx + 0] = p1[0];
        verts[idx + 1] = p1[1];
        verts[idx + 2] = p1[2];

        // Normal
        vec3 n1 = normalize(normTransform*n);
        verts[idx + 3] = n1[0];
        verts[idx + 4] = n1[1];
        verts[idx + 5] = n1[2];

        // UV
        verts[idx + 6] *= scale.x;
        verts[idx + 7] *= scale.x;
    }
    return verts;
}

void LSystemTree::setVertexData() {
    // Store the vertex data and other values to be used later when constructing the VAO
    int heightTesselation = getParam1() + 1;
    int thetaTesselation = getParam2()+ 2;
    int numBranchSteps = 5;//getParam3();

    lSystemRule rule = m_rulesDict['F'];
    std::vector<float> verts = makeBranch(numBranchSteps,
                                          heightTesselation,
                                          thetaTesselation,
                                          0.08, // Initial radius
                                          0.5,  // Initial height
                                          vec3(1.0, 1.0, 1.0),
                                          rule.angleX,
                                          rule.angleX,
                                          rule.translationUp);

    // Move the whole thing down so it rotates correctly around the origin
    mat4 Transform = translate(mat4(), vec3(0, -0.5, 0));
    for (int i = 0; i < verts.size()/8; i++){
        int idx = i*8;
        vec4 p = vec4(
                    verts[idx + 0],
                    verts[idx + 1],
                    verts[idx + 2], 1);

        p = Transform*p;
        verts[idx + 0] = p[0];
        verts[idx + 1] = p[1];
        verts[idx + 2] = p[2];
    }
    OpenGLShape::sendVertexData(verts);
}
