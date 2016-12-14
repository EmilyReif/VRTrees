#ifndef FORESTMAKER_H
#define FORESTMAKER_H
#include <memory>  // std::unique_ptr
#include "lsystem/lsystemgenerator.h"
#include "shapes/lsystemtree.h"
#include "shapes/OpenGLShape.h"

struct tree {
    std::shared_ptr<OpenGLShape> treeShape;
    mat4 modelMatrix;
};

class ForestMaker
{
public:
    ForestMaker();
    ~ForestMaker();
    std::vector<tree> getTrees();

private:
    std::vector<tree> m_trees;
    void makeTree0();
    void makeTree1();
    void makeTree2();
    void makeTree3();
    void makeTree4();
    void makeTree5();
    float random(float high, float low);
    float random();
};

#endif // FORESTMAKER_H
