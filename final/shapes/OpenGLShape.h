#ifndef OPENGLSHAPE_H
#define OPENGLSHAPE_H

#include "GL/glew.h"

#include <memory>
#include <vector>

#include "gl/datatype/VBO.h"
#include "gl/datatype/VBOAttribMarker.h"
#include "glm/glm.hpp"
using namespace glm;

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
    void setDrawMode(VBO::GEOMETRY_LAYOUT drawMode);
    void setNumVertices(int numVertices);
    int getParam1();
    int getParam2();
    int getParam3();
    void checkParamsMatchSettings();
    /** Sets the member variables based on the inputs **/
    void setParams(int p1, int p2, int p3);
    static float checkIntersectionPlane(vec4 d, vec4 eyeP, vec4 p0, vec4 n);

protected:

    /** Initialize the VBO with the given vertex data. */
    virtual void setVertexData();
    void sendVertexData(std::vector<float> verts);

    /** Enables the specified attribute and calls glVertexAttribPointer with the given arguments. */
    void setAttribute(GLuint index, GLuint numElementsPerVertex, int offset, VBOAttribMarker::DATA_TYPE type,
                      bool normalize);

    /** Build the VAO given the specified vertex data and atrributes */
    void buildVAO();

    void setTerrainData(GLfloat *data, int size, VBO::GEOMETRY_LAYOUT drawMode, int numVertices);


private:

    GLfloat *m_data;                            /// vector of floats containing the vertex data.
    GLsizeiptr m_size;                          /// size of the data array, in bytes.
    int m_param1;                               /// first shape parameter
    int m_param2;                               /// second shape parameter
    int m_param3;                               /// third shape parameter
    VBO::GEOMETRY_LAYOUT m_drawMode;            /// drawing mode
    int m_numVertices;                          /// number of vertices to be rendered
    std::vector<VBOAttribMarker> m_markers;     /// list of VBOAttribMarkers that describe how the data is laid out.
    std::unique_ptr<CS123::GL::VAO> m_VAO;      /// a wrapper for the vertex array object (VAO)
    GLuint m_textureID;


};

#endif // OPENGLSHAPE_H
