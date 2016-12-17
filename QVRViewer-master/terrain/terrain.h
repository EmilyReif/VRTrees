#ifndef TERRAIN_H
#define TERRAIN_H

#include "glm/glm.hpp"            // glm::vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include "glm/gtc/type_ptr.hpp"   // glm::value_ptr
#include <vector>

#include "terrainshape.h"

class Terrain {
public:
    Terrain();
    void init();
    void draw();
    glm::vec3 getPosition(int row, int col);

private:
    float randValue(int row, int col);
    float octave(int row, int col, float frequency, float amplitude);
    glm::vec3 getNormal(int row, int col);
    std::unique_ptr<TerrainShape> m_shape;
    const float m_numRows, m_numCols;

};

#endif // TERRAIN_H
