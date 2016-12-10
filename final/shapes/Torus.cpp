#include "Torus.h"
#include "gl/shaders/ShaderAttribLocations.h"
#include <iostream>
#include <tgmath.h>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>


Torus::Torus()
    : OpenGLShape()
{
    setVertexData();
}

Torus:: ~Torus()
{
}

void Torus::setVertexData() {
    // Store the vertex data and other values to be used later when constructing the VAO

    int thetaTesselation = getParam2() + 2;
    int phiTesselation = getParam1() + 2;
    float r = getParam3()/100.f;
    float pi = 3.14159265358979323;
    float R = 0.5;
    float thetaStep = 2 * pi/thetaTesselation;
    float phiStep = 2*pi/phiTesselation;

    std::vector<float> verts(0);
    for (int j = 0; j < phiTesselation; j++) {
        for (int i = 0; i < (thetaTesselation + 1); i++) {
            // Top vertex location
            verts.push_back((R + r * std::cos(thetaStep * i)) * std::cos(-phiStep * (j + 1)));
            verts.push_back((R + r * std::cos(thetaStep * i)) * std::sin(-phiStep * (j + 1)));
            verts.push_back(r * std::sin(thetaStep * i));

            // Top vertex normal
            glm::vec3 normal = glm::vec3((r * std::cos(thetaStep * i)) * std::cos(-phiStep * (j + 1)),
                                         (r * std::cos(thetaStep * i)) * std::sin(-phiStep * (j + 1)),
                                         r * std::sin(thetaStep * i));
            normal = glm::normalize(normal);
            verts.push_back(normal.x);
            verts.push_back(normal.y);
            verts.push_back(normal.z);

            // Top UV
            verts.push_back(static_cast<float>(j + 1)/phiTesselation);
            verts.push_back(static_cast<float>(i)/thetaTesselation);

            // Bottom vertex location
            verts.push_back((R + r * std::cos(thetaStep * i)) * std::cos(-phiStep * j));
            verts.push_back((R + r * std::cos(thetaStep * i)) * std::sin(-phiStep * j));
            verts.push_back(r * std::sin(thetaStep * i));

            // Top vertex normal
            normal = glm::vec3((r * std::cos(thetaStep * i)) * std::cos(-phiStep * j),
                                (r * std::cos(thetaStep * i)) * std::sin(-phiStep * j),
                                r * std::sin(thetaStep * i));
            normal = glm::normalize(normal);
            verts.push_back(normal.x);
            verts.push_back(normal.y);
            verts.push_back(normal.z);

            // Top UV
            verts.push_back(static_cast<float>(j)/phiTesselation);
            verts.push_back(static_cast<float>(i)/thetaTesselation);
        }
        // Add degenerate triangles.
        for (int j = 0; j < 16; j++) {
            verts.push_back(verts[verts.size() - 8]);
        }
    }
    OpenGLShape::sendVertexData(verts);
}
