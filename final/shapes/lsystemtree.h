#ifndef LSYSTEMTREE_H
#define LSYSTEMTREE_H
#include "OpenGLShape.h"
#include "Cone.h"
#include "lsystemtree.h"
#include "lsystem/lsystemgenerator.h"
#include "memory.h"
using namespace glm;

struct branch {
    vec3 scale;
    float angleXMultiplier;
    float angleZMultiplier;
    float translationMultiplier;
};

struct lSystemRule {
    float angleX;
    float angleZ;
    float translationUp;
    std::vector<branch> branches;
};


class LSystemTree
    : public OpenGLShape
{

public:
    LSystemTree(std::map<char, lSystemRule> rules);
    virtual ~LSystemTree();
    std::vector<float> makeBranch(int recursionDepth, int heightTesselation, int thetaTesselation, float radius, float height, glm::vec3 scale, float angleX, float angleZ, float translation);

protected:
    virtual void setVertexData();
    Cone m_cone;
    std::map<char, lSystemRule> m_rulesDict;
};


#endif // LSYSTEMTREE_H
