#ifndef OPENGLSHAPE_H
#define OPENGLSHAPE_H

//#include "GL/glew.h"

#include <memory>
#include <vector>

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFramebufferObject>
#include <QOpenGLDebugMessage>
#include <QOpenGLDebugLogger>
#include <QOpenGLTexture>

//#include "gl/datatype/VBO.h"
//#include "gl/datatype/VBOAttribMarker.h"
#include "glm/glm.hpp"            // vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // translate, scale, rotate

namespace CS123 { namespace GL {

class VAO;

}}

using namespace CS123::GL;

class OpenGLShape {
public:
    OpenGLShape();

    ~OpenGLShape();

    /** Draw the initialized geometry. */
    void draw();

    /** Setters/Getters for various private variables **/
    void setData(GLfloat *data);
    void setSize(int size);
    //void setDrawMode(VBO::GEOMETRY_LAYOUT drawMode);
    void setNumVertices(int numVertices);
    int getParam1();
    int getParam2();
    int getParam3();
    //void checkParamsMatchSettings();
    /** Sets the member variables based on the inputs **/
    void setParams(int p1, int p2, int p3);
    static float checkIntersectionPlane(glm::vec4 d, glm::vec4 eyeP, glm::vec4 p0, glm::vec4 n);

protected:

    /** Initialize the VBO with the given vertex data. */
    virtual void setVertexData();
    void sendVertexData(std::vector<float> verts);

    /** Enables the specified attribute and calls glVertexAttribPointer with the given arguments. */
    void setAttribute(int index, GLuint numElementsPerVertex, int offset, GLenum type,
                      bool normalize);

    /** Build the VAO given the specified vertex data and atrributes */
    void buildVAO();

private:

    GLfloat *m_data;                            /// vector of floats containing the vertex data.
    GLsizeiptr m_size;                          /// size of the data array, in bytes.
    int m_param1;                               /// first shape parameter
    int m_param2;                               /// second shape parameter
    int m_param3;                               /// third shape parameter
    //VBO::GEOMETRY_LAYOUT m_drawMode;            /// drawing mode
    int m_numVertices;                          /// number of vertices to be rendered
    //std::vector<VBOAttribMarker> m_markers;     /// list of VBOAttribMarkers that describe how the data is laid out.
    QOpenGLVertexArrayObject m_VAO;
    QOpenGLBuffer m_VBO;
    //std::unique_ptr<CS123::GL::VAO> m_VAO;      /// a wrapper for the vertex array object (VAO)
    QOpenGLTexture *m_texture;
    QOpenGLShaderProgram m_shader;


};

#endif // OPENGLSHAPE_H
