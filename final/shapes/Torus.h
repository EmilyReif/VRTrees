#ifndef TORUS_H
#define TORUS_H
#include "OpenGLShape.h"

class Torus
    : public OpenGLShape
{
public:
    Torus();
    virtual ~Torus();

protected:
    virtual void setVertexData();
};


#endif // TORUS_H
