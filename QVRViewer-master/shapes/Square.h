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
    static float checkIntersection(glm::vec4 ray, glm::vec4 eyeP);
    static glm::vec3 getNormal(glm::vec4 rayObj, glm::vec4 eyePObj, float minT);
    static glm::vec2 calculateUV(glm::vec4 point);
    static float enforceBounds(glm::vec4 eyeP, glm::vec4 d, float t, float max, float min);

protected:
    virtual void setVertexData();
    std::vector<float> makeSide(int rightIdx, int upIdx, int frontIdx, int normal);
    static float checkIntersectionSide(glm::vec4 d, glm::vec4 eyeP, int dimension, float norm);
};

#endif // SQUARE_H
