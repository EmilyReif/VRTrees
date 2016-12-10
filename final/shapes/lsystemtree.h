#ifndef LSYSTEMTREE_H
#define LSYSTEMTREE_H
#include "OpenGLShape.h"
#include "Cone.h"
#include "lsystemtree.h"
#include "lsystem/lsystemgenerator.h"
#include "memory.h"


struct rule {
    int numBranches;
    float angle;
    float scale;
};


class LSystemTree
    : public OpenGLShape
{
public:
    LSystemTree();
    virtual ~LSystemTree();
    std::vector<float> makeBranch(int recursionDepth, int heightTesselation, int thetaTesselation, float radius, float height, glm::vec3 scale, float angle, glm::vec3 translation);

protected:
    virtual void setVertexData();
    Cone m_cone;
    std::map<char, rule> m_rulesDict;
};


#endif // LSYSTEMTREE_H
