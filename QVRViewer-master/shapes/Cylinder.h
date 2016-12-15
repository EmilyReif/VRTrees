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
    static float checkIntersection(glm::vec4 ray, glm::vec4 eyeP);
    static float checkIntersectionBody(glm::vec4 ray, glm::vec4 eyeP);
    static float checkIntersectionCap(glm::vec4 ray, glm::vec4 eyeP, float top);
    static float enforceBoundsBody(glm::vec4 eyeP, glm::vec4 d, float t);
    static float enforceBoundsCap(glm::vec4 eyeP, glm::vec4 d, float t);


protected:
    virtual void setVertexData();
    Cap m_cap;
};

#endif // CYLINDER_H
