#include "Cap.h"
#include <tgmath.h>
#include <iostream>

Cap::Cap()
//Cap::Cap(int y, int radius, int thetaTesselation, int concentricTesselation)
{
}

Cap::~Cap() {
}

std::vector<float> Cap::createVertsVector(int radiusTesselation, int thetaTesselation, float radius, float height, float normalDirection) {
    float pi = 3.14159265358979323;
    float thetaStep = 2 * pi/thetaTesselation;
    float radiusStep = radius/radiusTesselation;

    std::vector<float> verts(0);

    for (int i = 0; i < radiusTesselation; i++) {
        for (int j = 0; j < (thetaTesselation + 1); j++) {
            // Top vertex position
            verts.push_back(radiusStep * i * std::cos(-normalDirection * thetaStep*j)); // X
            verts.push_back(height);                                 // Y
            verts.push_back(radiusStep * i * std::sin(-normalDirection * thetaStep*j)); // Z

            // Top vertex normal
            verts.push_back(0); // X
            verts.push_back(normalDirection);// Y
            verts.push_back(0); // Z

            // Top UV
            verts.push_back(radiusStep * i * std::cos(-thetaStep*j) + 0.5); // U
            verts.push_back(radiusStep * i * std::sin(-thetaStep*j) + 0.5); // V

            // Bottom vertex position
            verts.push_back(radiusStep * (i + 1) * std::cos(-normalDirection * thetaStep*j)); // X
            verts.push_back(height);                                       // Y
            verts.push_back(radiusStep * (i + 1) * std::sin(-normalDirection * thetaStep*j)); // Z

            // Bottom vertex normal
            verts.push_back(0); // X
            verts.push_back(normalDirection);// Y
            verts.push_back(0); // Z

            // Bottom UV
            verts.push_back(radiusStep * (i + 1) * std::cos(-thetaStep*j) + 0.5); // U
            verts.push_back(radiusStep * (i + 1) * std::sin(-thetaStep*j) + 0.5); // V
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
    return verts;
}
