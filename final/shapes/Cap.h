#ifndef CAP_H
#define CAP_H
#include "OpenGLShape.h"

class Cap
    : public OpenGLShape
{
public:
    Cap();
    virtual ~Cap();
    std::vector<float> createVertsVector(int radiusTesselation, int thetaTesselation, float radius, float height, float normalDirection);
};

#endif // CAP_H
