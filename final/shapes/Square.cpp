#include "Square.h"
#include "gl/shaders/ShaderAttribLocations.h"
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tgmath.h>
#include <glm/gtx/string_cast.hpp>

Square::Square()
    : OpenGLShape()
{
    setVertexData();
}

Square:: ~Square()
{
}

void Square::setVertexData() {
    // Store the vertex data and other values to be used later when constructing the VAO
    std::vector<GLfloat> quadData = {
                                    -1.f, +1.f, 0.f,
                                     1.f, 0.f, 0.f,
                                     0.f, 1.f, 0.f,

                                     -1.f, -1.f, 0.f,
                                     1.f, 0.f, 0.f,
                                     0.f, 0.f, 0.f,

                                     +1.f, +1.f, 0.f,
                                      1.f, 0.f, 0.f,
                                      1.f, 1.f, 0.f,

                                     +1.f, -1.f, 0.f,
                                     1.f, 0.f, 0.f,
                                     1.f, 0.f, 0.f
                                    };
    OpenGLShape::sendVertexData(quadData);
}

float Square::enforceBounds(vec4 eyeP, vec4 d, float t, float max, float min) {
    float x = eyeP.x + d.x*t;
    float y = eyeP.y + d.y*t;
    float z = eyeP.z + d.z*t;

    if ((t < 0) ||
        (x > max) || (x < min) ||
        (y > max) || (y < min) ||
        (z > max) || (z < min)) {
        return INT_MAX;
    }
    return t;
}

float Square::checkIntersectionSide(vec4 d, vec4 eyeP, int dimension, float norm) {
    vec4 p0 = vec4(0.0);
    vec4 n = vec4(0.0);
    p0[dimension] = norm * 0.5;
    n[dimension] = norm * 1.0;
    float epsilon = 0.00001;
    float t = OpenGLShape::checkIntersectionPlane(d, eyeP, p0, n);
    t = enforceBounds(eyeP, d, t, 0.5 + epsilon, -(0.5 + epsilon));
    return t;
}

float Square::checkIntersection(vec4 d, vec4 eyeP) {
    float t = INT_MAX;

    // Check for intersection with each side of the square.
    float norm = 1.0;
    for (int i = 0; i < 6; i++) {
        norm = ((i%2 == 0) ? 1.0 : -1.0);
        t = std::min(t, checkIntersectionSide(d, eyeP, i/2, norm));
    }
    return t;
}

vec3 Square::getNormal(vec4 rayObj, vec4 eyePObj, float minT) {

    float x = eyePObj.x + rayObj.x*minT;
    float y = eyePObj.y + rayObj.y*minT;
    float z = eyePObj.z + rayObj.z*minT;
    float e = 0.001;

    // Depending on where we are on the cube, the normal is just that side.
    vec3 normal = vec3(0.f, 0.f, 0.f);
    if (x > 0.5 - e) { normal.x = 1.f; }
    if (x < -0.5 + e) { normal.x = -1.f; }
    if (y > 0.5 - e) { normal.y = 1.f; }
    if (y < -0.5 + e) { normal.y = -1.f; }
    if (z > 0.5 - e) { normal.z = 1.f; }
    if (z < -0.5 + e) { normal.z= -1.f; }

    return normal;
}

vec2 Square::calculateUV(vec4 point){
    float e = 0.001;

    // Depending on where we are on the cube, the normal is just that side.
    vec2 uv = vec2(0.f, 0.f);
    if (point.x > 0.5 - e) {
        uv.x = 1.5 - point.z;
        uv.y = 1.5 - point.y;
    }
    if (point.x < -0.5 + e) {
        uv.x = point.z + 0.5;
        uv.y = 1.5 - point.y;
    }
    if (point.y > 0.5 - e) {
        uv.x = point.x + 0.5;
        uv.y = point.z + 0.5;
    }
    if (point.y < -0.5 + e) {
        uv.x = point.x + 0.5;
        uv.y = 1.5 - point.z;
    }
    if (point.z > 0.5 - e) {
        uv.x = point.x + 0.5;
        uv.y = 1.5 - point.y;
    }
    if (point.z < -0.5 + e) {
        uv.x = 1.5 - point.x;
        uv.y = 1.5 - point.y;
    }
    return uv;
}







