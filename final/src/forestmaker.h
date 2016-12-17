#ifndef FORESTMAKER_H
#define FORESTMAKER_H
#include <memory>  // std::unique_ptr
#include "lsystem/lsystemgenerator.h"
#include "shapes/lsystemtree.h"
#include "shapes/OpenGLShape.h"
#include "terrain/terrain.h"

struct tree {
    std::shared_ptr<OpenGLShape> treeShape;
    mat4 modelMatrix;
    float colorID;
};

class ForestMaker
{
public:
    ForestMaker();
    ~ForestMaker();
    std::vector<tree> getTrees();
    void drawTerrain();

private:
    std::vector<tree> m_trees;
    void makeTree0();
    void makeTree1();
    void makeTree2();
    void makeTree3();
    void makeTree4();
    void makeTree5();
    void makeTree6();
    void makeStandardForest();
    float random(float high, float low);
    float random();
    Terrain m_terrain;
};

#endif // FORESTMAKER_H
