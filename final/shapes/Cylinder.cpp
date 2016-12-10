#include "Cylinder.h"
#include "gl/shaders/ShaderAttribLocations.h"
#include <iostream>
#include <tgmath.h>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define __STDC_LIMIT_MACROS
#include <limits.h>

Cylinder::Cylinder()
    : OpenGLShape(),
    m_cap()
{
    setVertexData();
}

Cylinder:: ~Cylinder()
{
}

float Cylinder::enforceBoundsCap(glm::vec4 eyeP, glm::vec4 d, float t) {
    float x = eyeP.x + d.x * t;
    float z = eyeP.z + d.z * t;

    if ((t < 0) || (x*x + z*z > 0.25)) {
        t = INT_MAX;
    }
    return t;
}

float Cylinder::enforceBoundsBody(glm::vec4 eyeP, glm::vec4 d, float t) {
    if ((t < 0) ||
        (eyeP.y + d.y * t > 0.5) ||
        (eyeP.y + d.y * t < -0.5)) {
        return INT_MAX;
    }
    return t;
}

float Cylinder::checkIntersection(glm::vec4 d, glm::vec4 eyeP) {
    float t = checkIntersectionBody(d, eyeP);
    t = std::min(t, checkIntersectionCap(d, eyeP, -1));
    t = std::min(t, checkIntersectionCap(d, eyeP, 1));
    return t;
}

float Cylinder::checkIntersectionBody(glm::vec4 d, glm::vec4 eyeP) {
    float A = d.x*d.x + d.z*d.z;
    float B = 2.0*(eyeP.x*d.x + eyeP.z*d.z);
    float C = -0.25 + eyeP.x*eyeP.x + eyeP.z*eyeP.z;

    float discriminant = B*B - 4.0*A*C;
    if (discriminant < 0) {
        return INT_MAX;
    } else {
        float t0 = (-B + glm::sqrt(discriminant))/(2.0 * A);
        float t1 = (-B - glm::sqrt(discriminant))/(2.0 * A);
        t0 = enforceBoundsBody(eyeP, d, t0);
        t1 = enforceBoundsBody(eyeP, d, t1);
        return std::min(t0, t1);
    }
}

float Cylinder::checkIntersectionCap(glm::vec4 d, glm::vec4 eyeP, float top) {
    glm::vec4 p0 = glm::vec4(0.0, top * 0.5, 0.0, 0.0);
    glm::vec4 n = glm::vec4(0.0, top * 1.0, 0.0, 0.0);
    float t = OpenGLShape::checkIntersectionPlane(d, eyeP, p0, n);
    return enforceBoundsCap(eyeP, d, t);
}

void Cylinder::setVertexData() {
    // Store the vertex data and other values to be used later when constructing the VAO

    int heightTesselation = getParam1() + 1;
    int thetaTesselation = getParam2() + 2;
    float pi = 3.14159265358979323;
    float r = 0.5;
    float thetaStep = 2 * pi/thetaTesselation;
    float heightStep = 1.f/heightTesselation;

    std::vector<float> verts(0);

    for (int i = 0; i < heightTesselation; i++) {
        for (int j = 0; j < (thetaTesselation + 1); j++) {

            // Top vertex position
            verts.push_back(r * std::cos(-thetaStep * j)); // X
            verts.push_back(heightStep * (i + 1) - r);     // Y
            verts.push_back(r * std::sin(-thetaStep * j)); // Z

            // Top vertex normal
            glm::vec3 normal = glm::vec3(
                                        r * std::cos(-thetaStep * j),
                                        0,
                                        r * std::sin(-thetaStep * j));
            normal = glm::normalize(normal);
            verts.push_back(normal.x);
            verts.push_back(normal.y);
            verts.push_back(normal.z);

            // Top UV
            verts.push_back(static_cast<float>(j)/thetaTesselation);
            verts.push_back(-static_cast<float>(i + 1)/heightTesselation);

            // Bottom vertex position
            verts.push_back(r * std::cos(-thetaStep * j)); // X
            verts.push_back(heightStep * i - r);           // Y
            verts.push_back(r * std::sin(-thetaStep * j)); // Z

            // Bottom vertex normal
            verts.push_back(normal.x);
            verts.push_back(normal.y);
            verts.push_back(normal.z);

            // Bottom UV
            verts.push_back(static_cast<float>(j)/thetaTesselation);
            verts.push_back(-static_cast<float>(i)/heightTesselation);

        }
        // Add degenerate triangles.
        for (int j = 0; j < 16; j++) {
            verts.push_back(verts[verts.size() - 8]);
        }
    }
    // Add degenerate triangles.
    for (int i = 0; i < 16; i++) {
        verts.insert(verts.begin(), verts[8 - 1]);
    }

    std::vector<float> capTop = m_cap.createVertsVector(heightTesselation, thetaTesselation, r, -r, -1);
    std::vector<float> capBottom = m_cap.createVertsVector(heightTesselation, thetaTesselation, r, r, 1);
    verts.insert(verts.end(), capTop.begin(), capTop.end());
    verts.insert(verts.end(), capBottom.begin(), capBottom.end());
    OpenGLShape::sendVertexData(verts);
}
