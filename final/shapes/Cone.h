#ifndef CONE_H
#define CONE_H

#include "OpenGLShape.h"
#include "Cap.h"

class Cone
    : public OpenGLShape
{
public:
    Cone();
    virtual ~Cone();
    std::vector<float> createVertsVector(int heightTesselation, int thetaTesselation, float radius, float height);
    static float checkIntersection(glm::vec4 ray, glm::vec4 eyeP);
    static float checkIntersectionBody(glm::vec4 ray, glm::vec4 eyeP);
    static float checkIntersectionCap(glm::vec4 ray, glm::vec4 eyeP);
    static float enforceBoundsBody(glm::vec4 eyeP, glm::vec4 d, float t);
    static float enforceBoundsCap(glm::vec4 eyeP, glm::vec4 d, float t);
    static glm::vec3 getNormal(glm::vec4 rayObj, glm::vec4 eyePObj, float minT);
    static glm::vec2 calculateUV(glm::vec4 point);

protected:
    virtual void setVertexData();
    Cap m_cap;
};

#endif // CONE_H
