#include "forestmaker.h"
#include "../shapes/lsystemtree.h"
#include "../shapes/OpenGLShape.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "terrain/terrain.h"

ForestMaker::ForestMaker():
    m_trees(std::vector<tree>())
{
    m_terrain.init();
    makeStandardForest();
}

ForestMaker:: ~ForestMaker()
{
}

void ForestMaker::makeStandardForest ()
{
    for (int i = 0; i < 4; i++) {
        makeTree4();
        makeTree1();
        makeTree3();
        makeTree0();
        makeTree2();
    }
    int numTrees = m_trees.size();

    for (int i = 0; i < numTrees; i++) {
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::scale(transform, glm::vec3(random(0.5, 1.5)));
        float x = floor(random(0, 50));
        float z = floor(random(0, 50));
        glm::vec3 trans = m_terrain.getPosition(x, z);
        trans.y = trans.y/2 - 0.3;
        transform = glm::translate(transform, trans);
        float angle = random(0, 5);
        transform = glm::rotate(transform, angle, glm::vec3(0.f,1.f,0.f));
        m_trees[i].modelMatrix = transform;
        m_trees[i].colorID = random(0.2, 1.0);
    }
}

std::vector<tree> ForestMaker::getTrees() {
    return m_trees;
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
    glm::vec3 angle(0, pi/10, 0);
    rulesDict['F'] = lSystemRule{angle, 0.5f, 0.08f, .50f, branches, 6};

    // Set the location of the tree and add it to our forest.
    tree t = tree{std::make_unique<LSystemTree>(rulesDict)};
    m_trees.push_back(t);
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
    glm::vec3 angle(pi/2, pi/5, pi/7);
    rulesDict['F'] = lSystemRule{angle, 0.5f, 0.08f, .50f, branches, 6};

    // Set the location of the tree and add it to our forest.
    tree t = tree{std::make_unique<LSystemTree>(rulesDict)};
    m_trees.push_back(t);
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
    glm::vec3 angle(0, pi/2, 0);
    rulesDict['F'] = lSystemRule{angle, 1.f, 0.08f, .50f, branches, 6};

    // Set the location of the tree and add it to our forest.
    tree t = tree{std::make_unique<LSystemTree>(rulesDict)};
    m_trees.push_back(t);
}

// Experimental tree?
void ForestMaker::makeTree3() {
    // Initialize sphere OpenGLShape.
    float pi = 3.1415926535;
    float scaleRadius = 0.92;
    float scaleHeight = 0.7;

    // Array of branches that branch off from each node.
    std::vector<branch> branches(0);
    branches.push_back({scaleRadius, scaleHeight, 1, 1, -1, .1f});
    branches.push_back({scaleRadius, scaleHeight, 3, 1, -1, .6f});
    branches.push_back({scaleRadius, scaleHeight*.6f, -1, 1, -1, .7f});
    branches.push_back({scaleRadius, scaleHeight*.4f, -3, 1, -1, 1});


    // Define the rule constants and add the rule to the dictionary
    std::map<char, lSystemRule> rulesDict = {};
    glm::vec3 angle(pi/6, pi/8, pi/2);
    rulesDict['F'] = lSystemRule{angle, .75f, 0.03f, .50f, branches, 6};

    // Set the location of the tree and add it to our forest.
    tree t = tree{std::make_unique<LSystemTree>(rulesDict)};
    m_trees.push_back(t);
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
    glm::vec3 angle(0, pi/12, pi/3);
    rulesDict['F'] = lSystemRule{angle, 1, 0.02f, .50f, branches, 6};

    // Set the location of the tree and add it to our forest.
    tree t = tree{std::make_unique<LSystemTree>(rulesDict)};
    m_trees.push_back(t);
}

// Grass! (identical to tree5 but verrrry small.)
void ForestMaker::makeTree6() {
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
    glm::vec3 angle(0, pi/12, pi/3);
    rulesDict['F'] = lSystemRule{angle, 1, 0.02f, 0.1f, branches, 6};

    // Set the location of the tree and add it to our forest.
    tree t = tree{std::make_unique<LSystemTree>(rulesDict)};
    m_trees.push_back(t);
}



// Random version of 3d tree
void ForestMaker::makeTree5() {
    // Initialize sphere OpenGLShape.
    float pi = 3.1415926535;
    float scaleRadius = random();
    float scaleHeight = random();

    // Array of branches that branch off from each node.
    std::vector<branch> branches(0);
    branches.push_back({scaleRadius, scaleHeight, 1, -1, 1, 1});
    branches.push_back({scaleRadius, scaleHeight, 0, 1, 1, 1});
    branches.push_back({scaleRadius, scaleHeight,  0, 1, -1, 0});
    branches.push_back({scaleRadius, scaleHeight, 1, 1, 1, 0});

    // Define the rule constants and add the rule to the dictionary
    std::map<char, lSystemRule> rulesDict = {};
    glm::vec3 angle(random(0, pi/2),
               random(0, pi/2),
               random(0, pi/2));

    rulesDict['F'] = lSystemRule{angle, random(), random(0, 0.08f), random(0, .50f), branches, 6};

    // Set the location of the tree and add it to our forest.
    tree t = tree{std::make_unique<LSystemTree>(rulesDict)};
    m_trees.push_back(t);
}

void ForestMaker::drawTerrain(){
    m_terrain.draw();
}

// Just some quick helper functions to clean up the code.
float ForestMaker::random(float low, float high) {
    return ((double)std::rand()/RAND_MAX)*(high - low) + low;
}
float ForestMaker::random() {return ((double)std::rand()/RAND_MAX); }
