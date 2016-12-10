#include "Sphere.h"
#include "gl/shaders/ShaderAttribLocations.h"
#include <iostream>
#include <tgmath.h>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

Sphere::Sphere()
    : OpenGLShape()
{
    setVertexData();
}

Sphere:: ~Sphere()
{
}

void Sphere::setVertexData() {

    int phiTesselation = getParam1() + 1;
    int thetaTesselation = getParam2() + 2;
    float pi = 3.14159265358979323;
    float r = 0.5;
    float thetaStep = 2 * pi/thetaTesselation;
    float phiStep = pi/phiTesselation;

    std::vector<float> verts(0);
    for (int j = 0; j < phiTesselation; j++) {
        for (int i = 0; i < (thetaTesselation + 1); i++) {
            // Top vertex position
            verts.push_back(r * std::sin(phiStep * j) * std::cos(-thetaStep * i));
            verts.push_back(r * std::cos(phiStep * j));
            verts.push_back(r * std::sin(phiStep * j) * std::sin(-thetaStep * i));

            // Top vertex normal
            glm::vec3 normal = glm::vec3(r * std::sin(phiStep * j) * std::cos(-thetaStep * i),
                                         r * std::cos(phiStep * j),
                                         r * std::sin(phiStep * j) * std::sin(-thetaStep * i));

            normal = glm::normalize(normal);
            verts.push_back(normal.x);
            verts.push_back(normal.y);
            verts.push_back(normal.z);

            // Top UV
            verts.push_back(static_cast<float>(i)/thetaTesselation);
            verts.push_back(static_cast<float>(j)/phiTesselation);

            // Bottom vertex position
            verts.push_back(r * std::sin(phiStep * (j + 1)) * std::cos(-thetaStep * i));
            verts.push_back(r * std::cos(phiStep * (j + 1)));
            verts.push_back(r * std::sin(phiStep * (j + 1)) * std::sin(-thetaStep * i));

            // Bottom vertex normal
            normal = glm::vec3(r * std::sin(phiStep * (j + 1)) * std::cos(-thetaStep * i),
                                r * std::cos(phiStep * (j + 1)),
                                r * std::sin(phiStep * (j + 1)) * std::sin(-thetaStep * i));
            normal = glm::normalize(normal);
            verts.push_back(normal.x);
            verts.push_back(normal.y);
            verts.push_back(normal.z);

            // Bottom UV
            verts.push_back(static_cast<float>(i)/thetaTesselation);
            verts.push_back(static_cast<float>(j + 1)/phiTesselation);
        }
        // Add degenerate triangles.
        for (int j = 0; j < 16; j++) {
            verts.push_back(verts[verts.size() - 8]);
        }
    }
    OpenGLShape::sendVertexData(verts);
}

