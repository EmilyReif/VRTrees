#ifndef SPHERE_H
#define SPHERE_H

#include "OpenGLShape.h"

class Sphere
    : public OpenGLShape
{
public:
    Sphere();
    virtual ~Sphere();
    static float checkIntersection(vec4 ray, vec4 eyeP);
    static float enforceBounds(vec4 eyeP, vec4 d, float t);

protected:
    virtual void setVertexData();
};


#endif // SPHERE_H
