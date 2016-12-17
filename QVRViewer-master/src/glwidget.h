#ifndef GLWIDGET_H
#define GLWIDGET_H
#include "GL/glew.h"
#include <QGLWidget>
#include <QTimer>

#include "glm/glm.hpp"            // vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // translate, scale, rotate
#include "glm/gtc/type_ptr.hpp"   // value_ptr
#include "../shapes/Cap.h"
#include "../shapes/Cone.h"
#include "../shapes/Square.h"
#include "../shapes/Cylinder.h"
#include "../shapes/Sphere.h"
#include "../shapes/lsystemtree.h"
#include "../shapes/OpenGLShape.h"
#include <memory>  // std::unique_ptr
#include "forestmaker.h"
#include "glib/datatype/FBO.h"

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFramebufferObject>
#include <QOpenGLDebugMessage>
#include <QOpenGLDebugLogger>
#include <QOpenGLTexture>
#include <openvr.h>
#include <chrono>


class OpenGLShape;

using namespace CS123::GL;

class GLWidget : public QGLWidget {
    Q_OBJECT

public:
    GLWidget(QGLFormat format, QWidget *parent = 0);
    ~GLWidget();

signals:
    void framesPerSecond(float);
    void deviceIdentifier(const QString&);
    void frameSwap();
    void statusMessage(const QString&);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void keyPressEvent(QKeyEvent *e);

private:
    void initVR();

    void renderEye(vr::Hmd_Eye eye, bool screen);

    void updatePoses();

    void updateInput();


    void draw();
    void rebuildMatrices();

    glm::mat4x4 vrMatrixToQt(const vr::HmdMatrix34_t &mat);
    glm::mat4x4 vrMatrixToQt(const vr::HmdMatrix44_t &mat);

    // QMatrix is using qreal, so we need to overload to handle both platform cases
    void glUniformMatrix4(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    void glUniformMatrix4(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);

    glm::mat4x4 viewProjection(vr::Hmd_Eye eye);

    glm::mat4x4 perspectiveProjection(vr::Hmd_Eye eye);

    QString getTrackedDeviceString(vr::TrackedDeviceIndex_t device,
                                   vr::TrackedDeviceProperty prop,
                                   vr::TrackedPropertyError *error = 0);



    vr::IVRSystem *m_hmd;
    vr::TrackedDevicePose_t m_trackedDevicePose[vr::k_unMaxTrackedDeviceCount];
    glm::mat4x4 m_matrixDevicePose[vr::k_unMaxTrackedDeviceCount];

    glm::mat4x4 m_leftProjection, m_leftPose;
    glm::mat4x4 m_rightProjection, m_rightPose;
    glm::mat4x4 m_hmdPose;

    QOpenGLDebugLogger *m_logger;

    uint32_t m_eyeWidth, m_eyeHeight;
    //FBOHandle *m_leftBuffer, *m_rightBuffer;
    QOpenGLFramebufferObject *m_leftBuffer;
    QOpenGLFramebufferObject *m_rightBuffer;
    QOpenGLFramebufferObject *m_resolveBuffer;

    int m_frames;

    bool m_inputNext[vr::k_unMaxTrackedDeviceCount];
    bool m_inputPrev[vr::k_unMaxTrackedDeviceCount];





    int m_width;
    int m_height;

    GLuint m_texID;

    GLuint m_phongProgram;
    GLuint m_deferredSecondProgram;

    std::unique_ptr<OpenGLShape> m_quad;
    std::unique_ptr<ForestMaker> m_forestMaker;

    std::unique_ptr<FBO> m_defShadingFBO;

    bool m_firstPass;
    bool m_evenPass;

    glm::mat4 m_view, m_projection;

    /** For mouse interaction. */
    float m_angleX, m_angleY, m_zoom;
    QPoint m_prevMousePos;



    float m_currBranch;
    float m_branchPercent;

    bool m_animateBranches;

    bool m_drawFog;

    // For time things.
    std::chrono::steady_clock::time_point m_startTime;
};

#endif // GLWIDGET_H
