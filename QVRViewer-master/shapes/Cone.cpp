#include "Cone.h"
//#include "gl/shaders/ShaderAttribLocations.h"
#include <iostream>
//#include <tgmath.h>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
//#include "settings.h"

Cone::Cone()
    : OpenGLShape(),
      m_cap()
{
    setVertexData();
}

Cone:: ~Cone()
{
}

std::vector<float> Cone::createVertsVector(int heightTesselation, int thetaTesselation, float radius, float height, int branchIndex) {
    float pi = 3.14159265358979323;
    float thetaStep = 2 * pi/thetaTesselation;
    float heightStep = 2 * height/heightTesselation;

    std::vector<float> verts(0);

    for (int i = 0; i < heightTesselation; i++) {
        for (int j = 0; j < (thetaTesselation + 1); j++) {
            int linearScale = heightTesselation - i;
            // Top vertex position
            verts.push_back(radius*heightStep*(linearScale - 1) * std::cos(-thetaStep*j)); // X
            verts.push_back(heightStep * (i + 1) - height/2);                              // Y
            verts.push_back(radius*heightStep*(linearScale - 1) * std::sin(-thetaStep*j)); // Z

            // Top vertex normal
            glm::vec3 normal = glm::vec3(2/(std::sqrt(5)) * std::cos(-thetaStep*j),
                                         1/(std::sqrt(5)),
                                         2/(std::sqrt(5)) * std::sin(-thetaStep*j));
            normal = glm::normalize(normal);
            verts.push_back(normal.x);
            verts.push_back(normal.y);
            verts.push_back(normal.z);

            // Top UV
            verts.push_back(static_cast<float>(j)/thetaTesselation);
            verts.push_back(static_cast<float>(i + 1)/heightTesselation);

            verts.push_back(static_cast<float>(branchIndex));

            // Bottom vertex position
            verts.push_back(radius*heightStep*linearScale * std::cos(-thetaStep*j)); // X
            verts.push_back(heightStep * i - height/2);                              // Y
            verts.push_back(radius*heightStep*linearScale * std::sin(-thetaStep*j)); // Z

            // Bottom vertex normal
            verts.push_back(normal.x);
            verts.push_back(normal.y);
            verts.push_back(normal.z);

            // Top UV
            verts.push_back(static_cast<float>(j)/thetaTesselation);
            verts.push_back(static_cast<float>(i)/heightTesselation);

            verts.push_back(static_cast<float>(branchIndex));
        }
        // Add degenerate triangles.
        for (int j = 0; j < 18; j++) {
            verts.push_back(verts[verts.size() - 9]);
        }
    }
    // Add degenerate triangles.
    for (int i = 0; i < 18; i++) {
        verts.insert(verts.begin(), verts[9 - 1]);
    }
    return verts;
}

void Cone::setVertexData() {
    // Store the vertex data and other values to be used later when constructing the VAO
    int heightTesselation = getParam1() + 1;
    int thetaTesselation = getParam2() + 2;
    float r = 0.5;

    std::vector<float> verts = createVertsVector(heightTesselation, thetaTesselation, r, r, 0);
    std::vector<float> cap = m_cap.createVertsVector(heightTesselation, thetaTesselation, r, -r/2, -1);
    verts.insert(verts.end(), cap.begin(), cap.end());
    OpenGLShape::sendVertexData(verts);
}

