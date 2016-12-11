#ifndef SQUARE_H
#define SQUARE_H
#include "OpenGLShape.h"
#include <glm/vec3.hpp>

class Square
    : public OpenGLShape
{
public:
    Square();
    virtual ~Square();
    static float checkIntersection(vec4 ray, vec4 eyeP);
    static vec3 getNormal(vec4 rayObj, vec4 eyePObj, float minT);
    static vec2 calculateUV(vec4 point);
    static float enforceBounds(vec4 eyeP, vec4 d, float t, float max, float min);

protected:
    virtual void setVertexData();
    std::vector<float> makeSide(int rightIdx, int upIdx, int frontIdx, int normal);
    static float checkIntersectionSide(vec4 d, vec4 eyeP, int dimension, float norm);
};

#endif // SQUARE_H
