#include "OpenGLShape.h"
#include "GL/glu.h"
#include <memory>
//#include "gl/datatype/VAO.h"
//#include "gl/shaders/ShaderAttribLocations.h"
//#include "settings.h"
#include <iostream>
#include <QPainter>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace CS123::GL;

OpenGLShape::OpenGLShape():
    m_size(0),
    //m_drawMode(VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES),
    m_param1(5),//settings.shapeParameter1),
    m_param2(5),//settings.shapeParameter2),
    m_param3(5),//settings.shapeParameter3),
    m_numVertices(0),
    m_texture(0)
{
    // You shouldn't need to do anything here
    // Aren't initializer lists amazing?
}

OpenGLShape::~OpenGLShape()
{
    // You shouldn't need to do anything here
    // m_VAO's destructor will automatically be called
    // Aren't smart pointers amazing?
    //glDeleteTextures(1, &m_textureID);
    delete m_texture;
    m_VBO.destroy();
    m_VAO.destroy();
}

float OpenGLShape::checkIntersectionPlane(glm::vec4 d, glm::vec4 eyeP, glm::vec4 p0, glm::vec4 n) {
    float a = n.x*p0.x + n.y*p0.y + n.z*p0.z;
    float b = n.x*eyeP.x + n.y*eyeP.y + n.z*eyeP.z;
    float c = n.x*d.x + n.y*d.y + n.z*d.z;
    return (a - b)/c;
}

void OpenGLShape::setVertexData() {
}

void OpenGLShape::sendVertexData(std::vector<float> verts) {

    int vertsPerTriangle = 2;
    int dataSizePerVert = 3;
    int dataSizePerVertUV = 2;
    int bytesPerFloat = 4;
    setData(verts.data());
    setSize(verts.size());
    //setDrawMode(GL_TRIANGLE_STRIP);
    setNumVertices(verts.size()/(dataSizePerVert * vertsPerTriangle));
    setAttribute(0,
                 dataSizePerVert,
                 0,
                 GL_FLOAT,
                 false);
    setAttribute(1,
                 dataSizePerVert,
                 dataSizePerVert * bytesPerFloat,
                GL_FLOAT,
                 false);
    setAttribute(2,
                 dataSizePerVertUV,
                 2 * dataSizePerVert * bytesPerFloat,
                 GL_FLOAT,
                 false);
    buildVAO();
}

int OpenGLShape::getParam1() {
    return m_param1;
}

int OpenGLShape::getParam2() {
    return m_param2;
}

int OpenGLShape::getParam3() {
    return 11;
//    return m_param3;
}
/**
 * @param index OpenGL handle to the attribute location. These are specified in ShaderAttribLocations.h
 * @param numElementsPerVertex Number of elements per vertex. Must be 1, 2, 3 or 4 (e.g. position = 3 for x,y,z)
 * @param offset Offset in BYTES from the start of the array to the beginning of the first element
 * @param type Primitive type (FLOAT, INT, UNSIGNED_BYTE)
 * @param normalize
 */
void OpenGLShape::setAttribute( int index,
                                GLuint numElementsPerVertex,
                                int offset,
                                GLenum type,
                                bool normalize) {
    m_shader.bind();
    m_shader.setAttributeBuffer(index, type, offset, numElementsPerVertex);
    m_shader.enableAttributeArray(index);
    //m_markers.push_back(VBOAttribMarker(index, numElementsPerVertex, offset, type, normalize));
}

void OpenGLShape::buildVAO() {
    m_VAO.create();
    m_VAO.bind();
    m_VBO.create();
    m_VBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_VBO.bind();
    m_VBO.allocate(m_data, m_size);

    //CS123::GL::VBO vbo = VBO(m_data, m_size, m_markers, m_drawMode);
    //m_VAO = std::make_unique<VAO>(vbo, m_numVertices);
}

void OpenGLShape::setParams(int p1, int p2, int p3) {
    m_param1 = p1;
    m_param2 = p2;
    m_param3 = p3;
    setVertexData();
}

//void OpenGLShape::checkParamsMatchSettings() {
//    if ((m_param1 != settings.shapeParameter1) ||
//        (m_param2 != settings.shapeParameter2) ||
//        (m_param3 != settings.shapeParameter3)) {
//        setParams(settings.shapeParameter1, settings.shapeParameter2, settings.shapeParameter3);
//    }
//}

void OpenGLShape::draw() {
    //if (m_VAO.) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        m_VAO.bind();
        m_shader.bind();
        glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
        //m_VAO->draw();
        //m_VAO->unbind();
    //}
}

void OpenGLShape::setData(GLfloat *data) {
    m_data = data;
}

void OpenGLShape::setSize(int size) {
    m_size = size;
}

//void OpenGLShape::setDrawMode(VBO::GEOMETRY_LAYOUT drawMode) {
//    m_drawMode = drawMode;
//}

void OpenGLShape::setNumVertices(int numVertices) {
    m_numVertices = numVertices;
}

