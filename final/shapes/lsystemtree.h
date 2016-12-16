#ifndef LSYSTEMTREE_H
#define LSYSTEMTREE_H
#include "OpenGLShape.h"
#include "Cone.h"
#include "lsystemtree.h"
#include "lsystem/lsystemgenerator.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "memory.h"
using namespace glm;

struct branch {
    float scaleRadius;
    float scaleHeight;
    float angleXMultiplier;
    float angleYMultiplier;
    float angleZMultiplier;
    float translationMultiplier;
};

struct lSystemRule {
    vec3 angle;
    float translationUp;
    float initRadius;
    float initHeight;
    std::vector<branch> branches;
    int maxRecursionLevel;
};


class LSystemTree
        : public OpenGLShape
{

public:
    LSystemTree(std::map<char, lSystemRule> rules);
    virtual ~LSystemTree();
    std::vector<float> makeBranch(int recursionDepth, int heightTesselation, int thetaTesselation, float radius, float height, vec3 angle, float translation);

protected:
    virtual void setVertexData();
    std::vector<float> applyTransformToVerts(std::vector<float> &verts, mat4 transform);
    std::map<char, lSystemRule> m_rulesDict;

private:
    int maxDepth;
};


#endif // LSYSTEMTREE_H
