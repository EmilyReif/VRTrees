#ifndef GLWIDGET_H
#define GLWIDGET_H
#include "GL/glew.h"
#include <QGLWidget>
#include <QTimer>

#include "glm/glm.hpp"            // glm::vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include "glm/gtc/type_ptr.hpp"   // glm::value_ptr
#include "../shapes/Cap.h"
#include "../shapes/Cone.h"
#include "../shapes/Square.h"
#include "../shapes/Cylinder.h"
#include "../shapes/Sphere.h"
#include "../shapes/lsystemtree.h"
#include "../shapes/OpenGLShape.h"
#include <memory>  // std::unique_ptr

#include "gl/datatype/FBO.h"

class OpenGLShape;

using namespace CS123::GL;

class GLWidget : public QGLWidget {
    Q_OBJECT

public:
    GLWidget(QGLFormat format, QWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

private:
    void draw();
    void rebuildMatrices();

    int m_width;
    int m_height;

    GLuint m_texID;

    GLuint m_phongProgram;
    GLuint m_deferredSecondProgram;

    std::unique_ptr<OpenGLShape> m_quad;
    std::unique_ptr<LSystemTree> m_tree;

    std::unique_ptr<FBO> m_defShadingFBO;

    bool m_firstPass;
    bool m_evenPass;

    glm::mat4 m_view, m_projection;

    /** For mouse interaction. */
    float m_angleX, m_angleY, m_zoom;
    QPoint m_prevMousePos;
};

#endif // GLWIDGET_H
