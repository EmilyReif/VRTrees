#include "lsystemtree.h"
#include "gl/shaders/ShaderAttribLocations.h"
#include <iostream>
#include <tgmath.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "lsystem/lsystemgenerator.h"
#include <math.h>
using namespace glm;

LSystemTree::LSystemTree()
    : OpenGLShape(),
    m_cone(),
    m_rulesDict(std::map<char, rule>())
{
    rule rule1 = {2, M_PI/4, 0.7};
    m_rulesDict['F'] = rule1;


//    std::map<char, std::string> treeRules;
//    treeRules['F'] = "F[+F]F[-F]F";
//    lsystemGenerator *basicTree = new lsystemGenerator("F",treeRules);
//    basicTree->run(5);
//    std::cout << basicTree->getGenString() << std::endl;
    setVertexData();
}

LSystemTree:: ~LSystemTree()
{
}

std::vector<float> LSystemTree::makeBranch(int recursionDepth, int heightTesselation, int thetaTesselation, float radius, float height, glm::vec3 scale, float angle, glm::vec3 translation) {
    float pi = M_PI;
    std::vector<float> verts = m_cone.createVertsVector(heightTesselation, thetaTesselation, radius, height);
    if (recursionDepth < 1) {
        return verts;
    }

    // The smaller the branches get, the less tesselated they are
    heightTesselation = std::max(1, heightTesselation * 2/3);
    thetaTesselation = std::max(3, thetaTesselation * 2/3);

    // Also, the radius decreases.
    float newRad = std::max(radius * 0.75, 0.07);

    // Recursive call to make more branches!
    vec3 ntrans = vec3(0.0, 0.0, 0.0);
    std::vector<float> branch1 = makeBranch(recursionDepth - 1, heightTesselation, thetaTesselation, newRad, height, scale, 0, ntrans);
    ntrans.y += 0.5;
    std::vector<float> branch2 = makeBranch(recursionDepth - 1, heightTesselation, thetaTesselation, newRad, height, scale, angle, ntrans);
    std::vector<float> branch3 = makeBranch(recursionDepth - 1, heightTesselation, thetaTesselation, newRad, height, scale, 0, ntrans);
    ntrans.y += 0.5;
    std::vector<float> branch4 = makeBranch(recursionDepth - 1, heightTesselation, thetaTesselation, newRad, height, scale, -angle, ntrans);
    std::vector<float> branch5 = makeBranch(recursionDepth - 1, heightTesselation, thetaTesselation, newRad, height, scale, -angle, ntrans);

    // Concatonate all branches.
    verts.insert(verts.end(), branch1.begin(), branch1.end());
    verts.insert(verts.end(), branch2.begin(), branch2.end());
    verts.insert(verts.end(), branch3.begin(), branch3.end());
    verts.insert(verts.end(), branch4.begin(), branch4.end());
    verts.insert(verts.end(), branch5.begin(), branch5.end());

    // FACK
    glm::mat4 Transform = glm::mat4();
    Transform = glm::translate(Transform, translation);
    Transform = glm::scale(Transform, scale);
    Transform = glm::rotate(Transform, angle, glm::vec3(0, 0, 1));

    Transform = glm::translate(Transform, glm::vec3(0, height/2, 0));
    glm::mat3 normTransform = glm::inverse(glm::transpose(glm::mat3(Transform)));

    for (int i = 0; i < verts.size()/8; i++){
        int idx = i*8;
        glm::vec4 p = glm::vec4(
                    verts[idx + 0],
                    verts[idx + 1],
                    verts[idx + 2], 1);

        glm::vec3 n = glm::vec3(
                verts[idx + 3],
                verts[idx + 4],
                verts[idx + 5]);

        // Position
        glm::vec4 p1 = Transform*p;
        verts[idx + 0] = p1[0];
        verts[idx + 1] = p1[1];
        verts[idx + 2] = p1[2];

        // Normal
        glm::vec3 n1 = glm::normalize(normTransform*n);
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
    int numBranchSteps = 6;//getParam3();

    std::vector<float> verts = makeBranch(numBranchSteps,
                                          heightTesselation,
                                          thetaTesselation,
                                          0.08,
                                          0.5,
                                          glm::vec3(0.7, 0.7, 0.7),
                                          3.1415926535/10,
                                          glm::vec3(0, 0.5, 0));

    // Move the whole thing down so it rotates correctly around the origin
    glm::mat4 Transform = glm::translate(glm::mat4(), glm::vec3(0, -0.5, 0));
    for (int i = 0; i < verts.size()/8; i++){
        int idx = i*8;
        glm::vec4 p = glm::vec4(
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
