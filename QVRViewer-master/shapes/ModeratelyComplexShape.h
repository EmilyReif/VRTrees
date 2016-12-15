#ifndef MODERATELYCOMPLEXSHAPE_H
#define MODERATELYCOMPLEXSHAPE_H
#include "OpenGLShape.h"
#include "Cone.h"

class ModeratelyComplexShape
    : public OpenGLShape
{
public:
    ModeratelyComplexShape();
    virtual ~ModeratelyComplexShape();
    std::vector<float> makeBranch(int recursionDepth, int heightTesselation, int thetaTesselation, float radius, float height);

protected:
    virtual void setVertexData();
    Cone m_cone;
};


#endif // MODERATELYCOMPLEXSHAPE_H
