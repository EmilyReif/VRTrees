#ifndef LSYSTEMTREE_H
#define LSYSTEMTREE_H
#include "OpenGLShape.h"
#include "Cone.h"
#include "lsystem/lsystemgenerator.h"
#include "memory.h"

struct branch {
    float scaleRadius;
    float scaleHeight;
    float angleXMultiplier;
    float angleYMultiplier;
    float angleZMultiplier;
    float translationMultiplier;
};

struct lSystemRule {
    glm::vec3 angle;
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
    std::vector<float> makeBranch(int recursionDepth, int heightTesselation, int thetaTesselation, float radius, float height, glm::vec3 angle, float translation);

protected:
    virtual void setVertexData();
    std::vector<float> applyTransformToVerts(std::vector<float> &verts, glm::mat4 transform);
    std::map<char, lSystemRule> m_rulesDict;

private:
    int maxDepth;
};


#endif // LSYSTEMTREE_H
