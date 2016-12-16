#include "ModeratelyComplexShape.h"
//#include "gl/shaders/ShaderAttribLocations.h"
#include <iostream>
//#include <tgmath.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

ModeratelyComplexShape::ModeratelyComplexShape()
    : OpenGLShape(),
    m_cone()
{
    setVertexData();
}

ModeratelyComplexShape:: ~ModeratelyComplexShape()
{
}

std::vector<float> ModeratelyComplexShape::makeBranch(int recursionDepth, int heightTesselation, int thetaTesselation, float radius, float height ) {

    std::vector<float> verts = m_cone.createVertsVector(heightTesselation, thetaTesselation, radius, height);
    if (recursionDepth < 1) {
        return verts;
    }

    // The smaller the branches get, the less tesselated they are
    heightTesselation = glm::max(1, heightTesselation * 2/3);
    thetaTesselation = glm::max(3, thetaTesselation * 2/3);

    // Also, the radius decreases.
    float newRad = glm::max(radius * 0.75, 0.07);

    // Recursive call to make more branches!
    std::vector<float> branch1 = makeBranch(recursionDepth - 1, heightTesselation, thetaTesselation, newRad, height);
    std::vector<float> branch2 = makeBranch(recursionDepth - 1, heightTesselation, thetaTesselation, newRad, height);

    // Now, transform the branches so that they are smaller, rotated, and moved up the tree.
    float pi = 3.1415926535;
    glm::mat4 Transform = glm::mat4();

    // Scale, translate and rotate both
    Transform = glm::scale(Transform, glm::vec3(0.7, 0.7, 0.7));
    Transform = glm::translate(Transform, glm::vec3(0, height, 0));
    Transform = glm::rotate(Transform, -pi/4, glm::vec3(0, 1, 0));

    // Then, rotate each in opposite directions after.
    glm::mat4 Transform1 = glm::rotate(Transform, -pi/4, glm::vec3(0, 0, 1));
    Transform = glm::rotate(Transform, pi/4, glm::vec3(0, 0, 1));
    Transform = glm::translate(Transform, glm::vec3(0, height/2, 0));
    Transform1 = glm::translate(Transform1, glm::vec3(0, height/2, 0));

    // Translate normals
    glm::mat3 normTransform = glm::inverse(glm::transpose(glm::mat3(Transform)));
    glm::mat3 normTransform1 = glm::inverse(glm::transpose(glm::mat3(Transform)));

    for (int i = 0; i < branch1.size()/8; i++){
        int idx = i*8;
        glm::vec4 p = glm::vec4(
                    branch1[idx + 0],
                    branch1[idx + 1],
                    branch1[idx + 2], 1);
        glm::vec3 n = glm::vec3(
                branch1[idx + 3],
                branch1[idx + 4],
                branch1[idx + 5]);

        // Left branch
        // Position
        glm::vec4 p1 = Transform*p;
        branch1[idx + 0] = p1[0];
        branch1[idx + 1] = p1[1];
        branch1[idx + 2] = p1[2];

        // Normal
        glm::vec3 n1 = glm::normalize(normTransform*n);
        branch1[idx + 3] = n1[0];
        branch1[idx + 4] = n1[1];
        branch1[idx + 5] = n1[2];

        // UV
        branch1[idx + 6] *= 0.7;
        branch1[idx + 7] *= 0.7;

        // Right branch
        // Position
        glm::vec4 p2 = Transform1*p;
        branch2[idx + 0] = p2[0];
        branch2[idx + 1] = p2[1];
        branch2[idx + 2] = p2[2];

        // Normal
        glm::vec3 n2 = glm::normalize(normTransform1*n);
        branch2[idx + 3] = n2[0];
        branch2[idx + 4] = n2[1];
        branch2[idx + 5] = n2[2];

        // UV
        branch2[idx + 6] *= 0.7;
        branch2[idx + 7] *= 0.7;
    }
    // Concatonate all branches.
    verts.insert(verts.end(), branch1.begin(), branch1.end());
    verts.insert(verts.end(), branch2.begin(), branch2.end());
    return verts;
}

void ModeratelyComplexShape::setVertexData() {
    // Store the vertex data and other values to be used later when constructing the VAO
    int heightTesselation = getParam1() + 1;
    int thetaTesselation = getParam2()+ 2;
    int numBranchSteps = getParam3();

    std::vector<float> verts = makeBranch(numBranchSteps,
                                          heightTesselation,
                                          thetaTesselation,
                                          0.08,
                                          0.5);

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
