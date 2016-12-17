#include "terrain.h"

#include <math.h>
#include "../src/glib/shaders/ShaderAttribLocations.h"

Terrain::Terrain() : m_numRows(100), m_numCols(m_numRows)
{
}


/**
 * Returns a pseudo-random value between -1.0 and 1.0 for the given row and column.
 */
float Terrain::randValue(int row, int col) {
    return -1.0 + 2.0 * glm::fract(sin(row * 127.1f + col * 311.7f) * 43758.5453123f);
}


/**
 * Returns the object-space position for the terrain vertex at the given row and column.
 */
glm::vec3 Terrain::getPosition(int row, int col) {
    glm::vec3 finalposition = {10 * row/m_numRows - 5, 0,
                              10 * col/m_numCols - 5};
    return finalposition + glm::vec3(0, octave(row, col, 20., 1.) + octave(row, col, 10., .5) + octave(row, col, 5., .25) , 0);
}

float Terrain::octave(int row, int col, float frequency, float amplitude)
{
    glm::vec3 position;


    // TODO: Adjust position.y using value noise.
    float r = row/frequency;
    float c = col/frequency;

    int rf = floor(r);
    int cf = floor(c);

    int rc = ceil(r);
    int cc = ceil(c);

    float A = randValue(rf, cf);
    float B = randValue(rf, cc);
    float C = randValue(rc, cf);
    float D = randValue(rc, cc);


    float cfract = glm::fract(c);
    float rfract = glm::fract(r);


    float ABinter = glm::mix(A, B, cfract * cfract * (3-2*cfract));
    float CDinter = glm::mix(C, D, cfract * cfract * (3-2*cfract));
    position.y = glm::mix(ABinter, CDinter, rfract * rfract * (3-2*rfract)) * amplitude;

    return position.y;
}



/**
 * Returns the normal vector for the terrain vertex at the given row and column.
 */
glm::vec3 Terrain::getNormal(int row, int col) {
    // TODO: Compute the normal at the given row and column using the positions of the
    //       neighboring vertices.

    glm::vec3 p = getPosition(row, col);
    glm::vec3 n0 = getPosition(row, col + 1) - p;
    glm::vec3 n1 = getPosition(row -1, col + 1) - p;
    glm::vec3 n2 = getPosition(row -1, col) - p;
    glm::vec3 n3 = getPosition(row -1, col - 1) - p;
    glm::vec3 n4 = getPosition(row, col -1) - p;
    glm::vec3 n5 = getPosition(row +1, col + 1) - p;
    glm::vec3 n6 = getPosition(row + 1, col) - p;
    glm::vec3 n7 = getPosition(row + 1, col + 1) - p;
    return (glm::normalize(glm::cross(n1, n2)) +
            glm::normalize(glm::cross(n2, n1)) +
            glm::normalize(glm::cross(n3, n2)) +
            glm::normalize(glm::cross(n4, n3)) +
            glm::normalize(glm::cross(n5, n4)) +
            glm::normalize(glm::cross(n6, n5)) +
            glm::normalize(glm::cross(n7, n6)) +
            glm::normalize(glm::cross(n0, n7))) /8.f ;
}


/**
 * Initializes the terrain by storing positions and normals in a vertex buffer.
 */
void Terrain::init() {
    // TODO: Change from GL_LINE to GL_FILL in order to render full triangles instead of wireframe.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Initializes a grid of vertices using triangle strips.
    int numVertices = (m_numRows - 1) * (2 * m_numCols + 2);
    std::vector<glm::vec3> data(2 * numVertices);
    int index = 0;
    for (int row = 0; row < m_numRows - 1; row++) {
        for (int col = m_numCols - 1; col >= 0; col--) {
            data[index++] = getPosition(row, col);
            data[index++] = getNormal  (row, col);
            data[index++] = getPosition(row + 1, col);
            data[index++] = getNormal  (row + 1, col);
        }
        data[index++] = getPosition(row + 1, 0);
        data[index++] = getNormal  (row + 1, 0);
        data[index++] = getPosition(row + 1, m_numCols - 1);
        data[index++] = getNormal  (row + 1, m_numCols - 1);
    }

    // Initialize OpenGLShape.
    m_shape = std::make_unique<TerrainShape>();
    m_shape->setVertexData(&data[0][0], data.size() * 3, VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, numVertices);
    m_shape->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_shape->setAttribute(ShaderAttrib::NORMAL, 3, sizeof(glm::vec3), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_shape->buildVAO();
}


/**
 * Draws the terrain.
 */
void Terrain::draw()
{
    m_shape->draw();
}
