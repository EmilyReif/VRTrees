#include "forestmaker.h"
#include "../shapes/lsystemtree.h"
#include "../shapes/OpenGLShape.h"

ForestMaker::ForestMaker():
    m_trees(std::vector<std::unique_ptr<OpenGLShape>>()),
    m_tree(nullptr)
{
    makeTree3();
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
    float scaleRadius = 0.8;
    float scaleHeight = 0.65;

    // Array of branches that branch off from each node.
    std::vector<branch> branches(0);
    branches.push_back({scaleRadius, scaleHeight, 0, 0, 0, 0.0});
    branches.push_back({scaleRadius, scaleHeight, 0, 1, 0, 1});
    branches.push_back({scaleRadius, scaleHeight, 0, 0, 0, 1});
    branches.push_back({scaleRadius, scaleHeight, 0, -1, 0, 2});

    // Define the rule constants and add the rule to the dictionary
    std::map<char, lSystemRule> rulesDict = {};
    vec3 angle(0, pi/10, 0);
    rulesDict['F'] = lSystemRule{angle, 0.5, 0.08, 0.5, branches, 6};
    m_trees.push_back(std::make_unique<LSystemTree>(rulesDict));
}

// 3D tree
void ForestMaker::makeTree1() {
    // Initialize sphere OpenGLShape.
    float pi = 3.1415926535;
    float scaleRadius = 0.6;
    float scaleHeight = 0.7;

    // Array of branches that branch off from each node.
    std::vector<branch> branches(0);
    branches.push_back({scaleRadius, scaleHeight, 1, -1, 1, 1});
    branches.push_back({scaleRadius, scaleHeight, 0, 1, 1, 1});
    branches.push_back({scaleRadius, scaleHeight,  0, 1, -1, 0});
    branches.push_back({scaleRadius, scaleHeight, 1, 1, 1, 0});

    // Define the rule constants and add the rule to the dictionary
    std::map<char, lSystemRule> rulesDict = {};
    vec3 angle(pi/2, pi/5, pi/7);
    rulesDict['F'] = lSystemRule{angle, 0.5, 0.08, 0.5, branches, 6};
    m_trees.push_back(std::make_unique<LSystemTree>(rulesDict));
}

// Weird square spirals
void ForestMaker::makeTree2() {
    // Initialize sphere OpenGLShape.
    float pi = 3.1415926535;
    float scaleRadius = 0.6;
    float scaleHeight = 0.6;

    // Array of branches that branch off from each node.
    std::vector<branch> branches(0);
    branches.push_back({scaleRadius, scaleHeight, 0, 1, 0, 1});
    branches.push_back({scaleRadius, scaleHeight,  0, -1, 0, 0.5});

    // Define the rule constants and add the rule to the dictionary
    std::map<char, lSystemRule> rulesDict = {};
    vec3 angle(0, pi/2, 0);
    rulesDict['F'] = lSystemRule{angle, 1, 0.08, 0.5, branches, 6};
    m_trees.push_back(std::make_unique<LSystemTree>(rulesDict));
}

// Experimental tree?
void ForestMaker::makeTree3() {
    // Initialize sphere OpenGLShape.
    float pi = 3.1415926535;
    float scaleRadius = 0.92;
    float scaleHeight = 0.7;

    // Array of branches that branch off from each node.
    std::vector<branch> branches(0);
    branches.push_back({scaleRadius, scaleHeight, 1, 1, -1, .1});
    branches.push_back({scaleRadius, scaleHeight, 3, 1, -1, .6});
    branches.push_back({scaleRadius, scaleHeight*.6f, -1, 1, -1, .7});
    branches.push_back({scaleRadius, scaleHeight*.4f, -3, 1, -1, 1});


    // Define the rule constants and add the rule to the dictionary
    std::map<char, lSystemRule> rulesDict = {};
    vec3 angle(pi/6, pi/8, pi/2);
    rulesDict['F'] = lSystemRule{angle, .75, 0.03, 1, branches, 6};
    m_trees.push_back(std::make_unique<LSystemTree>(rulesDict));
}

// Skinny tree (like 3D tree but with slightly different start states.)
void ForestMaker::makeTree4() {
    // Initialize sphere OpenGLShape.
    float pi = 3.1415926535;
    float scaleRadius = 0.5;
    float scaleHeight = .8;
    float scaleHeight1 = 0.5;

    // Array of branches that branch off from each node.
    std::vector<branch> branches(0);
    branches.push_back({scaleRadius, scaleHeight, 0, 1, -1, 1});
    branches.push_back({scaleRadius, scaleHeight1, 0, 1, 1, 1});
    branches.push_back({scaleRadius, scaleHeight1, 0, -1, 1, 0});
    branches.push_back({scaleRadius, scaleHeight, 0, 1, 1, 0});

    // Define the rule constants and add the rule to the dictionary.
    std::map<char, lSystemRule> rulesDict = {};
    vec3 angle(0, pi/12, pi/3);
    rulesDict['F'] = lSystemRule{angle, 1, 0.02, 0.5, branches, 6};
    m_trees.push_back(std::make_unique<LSystemTree>(rulesDict));
}
