#ifndef TERRAIN_H
#define TERRAIN_H


#include "glm/glm.hpp"            // glm::vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include "glm/gtc/type_ptr.hpp"   // glm::value_ptr
#include <vector>

#include "OpenGLShape.h"

class Terrain
        : public OpenGLShape
{
public:
    Terrain();
    virtual ~Terrain();
     void init();

protected:
    virtual void setVertexData();
private:
    float randValue(int row, int col);
    glm::vec3 getPosition(int row, int col);
    float octave(int row, int col, float frequency, float amplitude);
    glm::vec3 getNormal(int row, int col);
    const float m_numRows, m_numCols;
    std::vector<float> createVertsVector();
};

#endif // TERRAIN_H
