#include "forestmaker.h"
#include "../shapes/lsystemtree.h"
#include "../shapes/OpenGLShape.h"

ForestMaker::ForestMaker():
    m_trees(std::vector<std::unique_ptr<OpenGLShape>>()),
    m_tree(nullptr)
{
    makeTree0();
}

ForestMaker:: ~ForestMaker()
{
}

void ForestMaker::drawTrees()
{
    int numTrees = m_trees.size();
    for (int i = 0; i < numTrees; i++) {
        m_trees[i]->draw();
    }
}

// Original tree!
void ForestMaker::makeTree0() {
    // Initialize sphere OpenGLShape.
    float pi = 3.1415926535;
    vec3 scale = vec3(0.7, 0.7, 0.7);

    // Array of branches that branch off from each node.
    std::vector<branch> branches(0);
    branches.push_back({scale, 0, 0, 0.0});
    branches.push_back({scale, 1, 0, 1});
    branches.push_back({scale, 0, 0, 1});
    branches.push_back({scale, -1, 0, 2});

    // Define the rule constants and add the rule to the dictionary
    std::map<char, lSystemRule> rulesDict = {};
    rulesDict['F'] = lSystemRule{pi/10, 0, 0.5, branches};
    m_trees.push_back(std::make_unique<LSystemTree>(rulesDict));
}

// 3D tree
void ForestMaker::makeTree1() {
    // Initialize sphere OpenGLShape.
    float pi = 3.1415926535;
    vec3 scale = vec3(.5, .7, .5);

    // Array of branches that branch off from each node.
    std::vector<branch> branches(0);
    branches.push_back({scale, 1, -1, 1});
    branches.push_back({scale, 1, 1, 1});
    branches.push_back({scale, -1, 1, 0});
    branches.push_back({scale, 1, 1, 0});

    // Define the rule constants and add the rule to the dictionary
    std::map<char, lSystemRule> rulesDict = {};
    rulesDict['F'] = lSystemRule{pi/5, pi/7, 0.5, branches};
    m_trees.push_back(std::make_unique<LSystemTree>(rulesDict));
}

// Weird square spirals
void ForestMaker::makeTree2() {
    // Initialize sphere OpenGLShape.
    float pi = 3.1415926535;
    vec3 scale = vec3(0.6, 0.6, 0.6);

    // Array of branches that branch off from each node.
    std::vector<branch> branches(0);
    branches.push_back({scale, 1, 0, 1});
    branches.push_back({scale, -1, 0, 0.5});

    // Define the rule constants and add the rule to the dictionary
    std::map<char, lSystemRule> rulesDict = {};
    rulesDict['F'] = lSystemRule{pi/2, pi/6, 0.5, branches};
    m_trees.push_back(std::make_unique<LSystemTree>(rulesDict));
}

// 3D tree
void ForestMaker::makeTree3() {
    // Initialize sphere OpenGLShape.
    float pi = 3.1415926535;
    vec3 scale = vec3(.6, .7, .6);

    // Array of branches that branch off from each node.
    std::vector<branch> branches(0);
    branches.push_back({scale, 1, 1, .3});
    branches.push_back({scale, 1, 2, .4});
    branches.push_back({scale, 1, 3, .5});
    branches.push_back({scale, 1, 4, .6});
    branches.push_back({scale, 1, 5, .7});
    branches.push_back({scale, 1, 6, .8});


    // Define the rule constants and add the rule to the dictionary
    std::map<char, lSystemRule> rulesDict = {};
    rulesDict['F'] = lSystemRule{pi/3, pi/3, 0.5, branches};
    m_trees.push_back(std::make_unique<LSystemTree>(rulesDict));
}
