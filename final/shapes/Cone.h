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
    static std::vector<float> createVertsVector(int heightTesselation, int thetaTesselation, float radius, float height, int branchIndex);
    static float checkIntersection(vec4 ray, vec4 eyeP);
    static float checkIntersectionBody(vec4 ray, vec4 eyeP);
    static float checkIntersectionCap(vec4 ray, vec4 eyeP);
    static float enforceBoundsBody(vec4 eyeP, vec4 d, float t);
    static float enforceBoundsCap(vec4 eyeP, vec4 d, float t);
    static vec3 getNormal(vec4 rayObj, vec4 eyePObj, float minT);
    static vec2 calculateUV(vec4 point);

protected:
    virtual void setVertexData();
    Cap m_cap;
};

#endif // CONE_H
