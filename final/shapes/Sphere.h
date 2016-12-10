#ifndef SPHERE_H
#define SPHERE_H

#include "OpenGLShape.h"

class Sphere
    : public OpenGLShape
{
public:
    Sphere();
    virtual ~Sphere();
    static float checkIntersection(glm::vec4 ray, glm::vec4 eyeP);
    static float enforceBounds(glm::vec4 eyeP, glm::vec4 d, float t);

protected:
    virtual void setVertexData();
};


#endif // SPHERE_H
