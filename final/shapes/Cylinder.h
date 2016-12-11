#ifndef CYLINDER_H
#define CYLINDER_H
#include "OpenGLShape.h"
#include "Cap.h"
#include <glm/vec3.hpp>

class Cylinder
    : public OpenGLShape
{
public:
    Cylinder();
    virtual ~Cylinder();
    static float checkIntersection(vec4 ray, vec4 eyeP);
    static float checkIntersectionBody(vec4 ray, vec4 eyeP);
    static float checkIntersectionCap(vec4 ray, vec4 eyeP, float top);
    static float enforceBoundsBody(vec4 eyeP, vec4 d, float t);
    static float enforceBoundsCap(vec4 eyeP, vec4 d, float t);


protected:
    virtual void setVertexData();
    Cap m_cap;
};

#endif // CYLINDER_H
