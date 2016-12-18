#include "glwidget.h"

#include "cs123_lib/resourceloader.h"
#include "cs123_lib/errorchecker.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <iostream>
#include "settings.h"

#include "../src/glib/textures/Texture2D.h"
#include "../src/glib/shaders/ShaderAttribLocations.h"
#include "../shapes/Cap.h"
#include "../shapes/Cone.h"
#include "../shapes/Square.h"
#include "../shapes/Cylinder.h"
#include "../shapes/ModeratelyComplexShape.h"
#include "../shapes/Sphere.h"
#include "../shapes/OpenGLShape.h"
#include "../shapes/lsystemtree.h"
#include "forestmaker.h"

#include <chrono>

#include "glm/gtx/string_cast.hpp"

#define NEAR_CLIP 0.1f
#define FAR_CLIP 100000000.f

using namespace CS123::GL;

GLWidget::GLWidget(QGLFormat format, QWidget *parent)
    : QGLWidget(format, parent),
      m_width(width()), m_height(height()),
      m_phongProgram(0), m_deferredSecondProgram(0),
      m_quad(nullptr),
      m_forestMaker(nullptr),
      m_defShadingFBO(nullptr),
      m_angleX(-0.5f), m_angleY(0.5f), m_zoom(4.f),
      m_texID(0),
      m_hmd(0),
      m_eyeWidth(0),
      m_eyeHeight(0),
      m_leftBuffer(0),
      m_rightBuffer(0),
      m_frames(0),
      m_currBranch(0),
      m_branchPercent(0),
      m_animateBranches(true),
      m_drawFog(true),
      m_drawSnow(false),
      m_justNormals(false),
      m_justPos(false),
      m_fogDist(1.4),
      m_location(glm::vec3(2.f, 1.f, 1.5f))

{
    setFocusPolicy(Qt::StrongFocus);
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL() {
    ResourceLoader::initializeGlew();
    glEnable(GL_DEPTH_TEST);

    // Set the color to set the screen when the color buffer is cleared.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Create shader programs.
    m_phongProgram = ResourceLoader::createShaderProgram(
                ":/shaders/deferredShadingFirst.vert", ":/shaders/deferredShadingFirst.frag");
    m_deferredSecondProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/deferredShadingSecond.frag");

    m_quad = std::make_unique<Square>();
    m_forestMaker = std::make_unique<ForestMaker>();

    // Initialize textures.
    QImage image(":/images/noiseSmall.png");
    glGenTextures(1, &m_texID);
    glBindTexture(GL_TEXTURE_2D, m_texID);
    glTexImage2D(
         GL_TEXTURE_2D,
         0,
         GL_RGBA,
         image.width(),
         image.height(),
         0,
         GL_RGBA,
         GL_UNSIGNED_BYTE,
         image.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);
    initVR();
    m_startTime = std::chrono::steady_clock::now();
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw();
}

void GLWidget::draw() {


    std::chrono::steady_clock::time_point currTime = std::chrono::steady_clock::now();

    std::chrono::milliseconds time_span = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - m_startTime);

    if (m_animateBranches) {
    m_currBranch = (int)(time_span.count()/3000.) % 10;
    if (m_currBranch == 9) {
        m_animateBranches = false;
    }
    }
    m_branchPercent = (time_span.count() % 3000) /3000.f;


    if (m_hmd)
    {
        updatePoses();
        updateInput();
        glViewport(0, 0, m_eyeWidth, m_eyeHeight);

        QRect sourceRect(0, 0, m_eyeWidth, m_eyeHeight);

        glEnable(GL_MULTISAMPLE);
        renderEye(vr::Eye_Left, false);

        QRect targetLeft(0, 0, m_eyeWidth, m_eyeHeight);
        QOpenGLFramebufferObject::blitFramebuffer(m_resolveBuffer, targetLeft,
                                                  m_leftBuffer, sourceRect);

        glEnable(GL_MULTISAMPLE);
        renderEye(vr::Eye_Right, false);
        QRect targetRight(m_eyeWidth, 0, m_eyeWidth, m_eyeHeight);
        QOpenGLFramebufferObject::blitFramebuffer(m_resolveBuffer, targetRight,
                                                  m_rightBuffer, sourceRect);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glViewport(0, 0, width(), height());
    glDisable(GL_MULTISAMPLE);
    renderEye(vr::Eye_Right, true);

    if (m_hmd)
    {
        vr::VRTextureBounds_t leftRect = { 0.0f, 0.5f, 0.5f, 1.0f };
        vr::VRTextureBounds_t rightRect = { 0.5f, 0.5f, 1.0f, 1.0f };
        vr::Texture_t composite = { (void*)m_resolveBuffer->texture(), vr::TextureType_OpenGL, vr::ColorSpace_Gamma };

        vr::VRCompositor()->Submit(vr::Eye_Left, &composite, &leftRect);
        vr::VRCompositor()->Submit(vr::Eye_Right, &composite, &rightRect);
    }

    update();


}

void GLWidget::renderEye(vr::Hmd_Eye eye, bool screen)
{

    glUseProgram(m_phongProgram);
    m_defShadingFBO->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glActiveTexture(GL_TEXTURE0);

    glm::mat4x4 loc = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));

    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "view"),  1, GL_FALSE, glm::value_ptr(viewProjection(eye)));
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "projection"),  1, GL_FALSE, glm::value_ptr(glm::transpose(perspectiveProjection(eye))));
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"),  1, GL_FALSE, glm::value_ptr(loc));
    glUniform1f(glGetUniformLocation(m_phongProgram, "currentBranch"), m_currBranch);
    glUniform1f(glGetUniformLocation(m_phongProgram, "percent"), m_branchPercent);

    std::vector<tree> trees = m_forestMaker->getTrees();
    {
        int numTrees = trees.size();
        for (int i = 0; i < numTrees; i++) {
            loc = trees[i].modelMatrix;
            glUniform1f(glGetUniformLocation(m_phongProgram, "colorID"),  trees[i].colorID);
            glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"),  1, GL_FALSE, glm::value_ptr(loc));
            trees[i].treeShape->draw();
        }
        loc = glm::mat4x4();
        loc = glm::scale(loc, glm::vec3(1, 0.5, 1));
        glUniform1f(glGetUniformLocation(m_phongProgram, "colorID"),  1);
        glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"),  1, GL_FALSE, glm::value_ptr(loc));
        m_forestMaker->drawTerrain();
    }
    m_defShadingFBO->unbind();

    // Bind the VR buffer
    if (!screen) {
        if (eye == vr::Eye_Left) {
            m_leftBuffer->bind();
        } else {
            m_rightBuffer->bind();
        }
    }

    glUseProgram(m_deferredSecondProgram);
    glUniform1i(glGetUniformLocation(m_deferredSecondProgram, "NormalAndDiffuse"), 0);
    glUniform1i(glGetUniformLocation(m_deferredSecondProgram, "PosAndSpec"), 1);
    glUniform1i(glGetUniformLocation(m_deferredSecondProgram, "Noise"), 2);
    glUniform1i(glGetUniformLocation(m_deferredSecondProgram, "DrawFog"), m_drawFog);
    glUniform1i(glGetUniformLocation(m_deferredSecondProgram, "DrawSnow"), m_drawSnow);
    glUniform1i(glGetUniformLocation(m_deferredSecondProgram, "JustNormal"), m_justNormals);
    glUniform1i(glGetUniformLocation(m_deferredSecondProgram, "JustPos"), m_justPos);
    glUniform1f(glGetUniformLocation(m_deferredSecondProgram, "FogDist"), m_fogDist);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    m_defShadingFBO->getColorAttachment(0).bind();
    glActiveTexture(GL_TEXTURE1);
    m_defShadingFBO->getColorAttachment(1).bind();
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_texID);

    glUniformMatrix4fv(glGetUniformLocation(m_deferredSecondProgram, "view"),  1, GL_FALSE, glm::value_ptr(viewProjection(eye)));
    glUniformMatrix4fv(glGetUniformLocation(m_deferredSecondProgram, "projection"),  1, GL_FALSE, glm::value_ptr(glm::transpose(perspectiveProjection(eye))));
    m_quad->draw();

    // Finally, unbind everything.
    if (!screen) {
        if (eye == vr::Eye_Left) {
            m_leftBuffer->release();
        } else {
            m_rightBuffer->release();
        }
    }

    glUseProgram(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// This is called at the beginning of the program between initializeGL and
// the first paintGL call, as well as every time the window is resized.
void GLWidget::resizeGL(int w, int h) {
    m_width = w;
    m_height = h;

    // TODO: [Task 5] Initialize FBOs here, with dimensions m_width and m_height.
    m_defShadingFBO = std::make_unique<FBO>(
                2,
                FBO::DEPTH_STENCIL_ATTACHMENT::DEPTH_ONLY,
                m_width, m_height,
                TextureParameters::WRAP_METHOD::REPEAT,
                TextureParameters::FILTER_METHOD::LINEAR,
                GL_FLOAT);
    rebuildMatrices();
}

/// Mouse interaction code below.
void GLWidget::mousePressEvent(QMouseEvent *event) {
    m_prevMousePos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    m_angleX += 3.f * (event->x() - m_prevMousePos.x()) / (float) m_width;
    m_angleY += 3.f * (event->y() - m_prevMousePos.y()) / (float) m_height;
    m_prevMousePos = event->pos();
    rebuildMatrices();
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_F:
        m_drawFog = !m_drawFog;
        break;
    case Qt::Key_T:
        m_animateBranches = true;
        m_startTime = std::chrono::steady_clock::now();
        break;
    case Qt::Key_N:
        m_justNormals = !m_justNormals;
        break;
    case Qt::Key_P:
        m_justPos = !m_justPos;
        break;
    case Qt::Key_S:
        m_drawSnow = !m_drawSnow;
        break;
    case Qt::Key_Comma:
        m_fogDist = glm::clamp(m_fogDist - 0.2, 1.4, 4.4);
        break;
    case Qt::Key_Period:
        m_fogDist = glm::clamp(m_fogDist + 0.2, 1.4, 4.4);
        break;
    case Qt::Key_Space:
        m_location += glm::mat3x3(m_hmdPose) * glm::vec3(0.0, 0.0, 0.5);
    }

}

void GLWidget::wheelEvent(QWheelEvent *event) {
    m_zoom -= event->delta() / 100.f;
    rebuildMatrices();
}

void GLWidget::rebuildMatrices() {
    m_view = glm::translate(glm::vec3(0.f, -1.f, -m_zoom)) *
             glm::rotate(m_angleY, glm::vec3(1.f,0.f,0.f)) *
             glm::rotate(m_angleX, glm::vec3(0.f,1.f,0.f));

    m_projection = glm::perspective(35.0f, (float)m_width/m_height, 0.1f, 100000000.f);
    update();
}

void GLWidget::initVR() {
    vr::EVRInitError error = vr::VRInitError_None;
    m_hmd = vr::VR_Init(&error, vr::VRApplication_Scene);

    if (error != vr::VRInitError_None) {
        m_hmd = 0;

        std::cerr << vr::VR_GetVRInitErrorAsEnglishDescription(error) << std::endl;
        return;
    }

    m_rightProjection = vrMatrixToQt(m_hmd->GetProjectionMatrix(vr::Eye_Right, NEAR_CLIP, FAR_CLIP));
    m_rightPose = glm::inverse(vrMatrixToQt(m_hmd->GetEyeToHeadTransform(vr::Eye_Right)));

    m_leftProjection = vrMatrixToQt(m_hmd->GetProjectionMatrix(vr::Eye_Left, NEAR_CLIP, FAR_CLIP));
    m_leftPose = glm::inverse(vrMatrixToQt(m_hmd->GetEyeToHeadTransform(vr::Eye_Left)));

    QString ident;
    ident.append("QVRViewer - ");
    ident.append(getTrackedDeviceString(vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_TrackingSystemName_String));
    ident.append(" ");
    ident.append(getTrackedDeviceString(vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_SerialNumber_String));
    emit deviceIdentifier(ident);

    // setup frame buffers for eyes
    m_hmd->GetRecommendedRenderTargetSize(&m_eyeWidth, &m_eyeHeight);

    QOpenGLFramebufferObjectFormat buffFormat;
    buffFormat.setAttachment(QOpenGLFramebufferObject::Depth);
    buffFormat.setInternalTextureFormat(GL_RGBA8);
    buffFormat.setSamples(4);

    m_leftBuffer = new QOpenGLFramebufferObject(m_eyeWidth, m_eyeHeight, buffFormat);
    m_rightBuffer = new QOpenGLFramebufferObject(m_eyeWidth, m_eyeHeight, buffFormat);

    QOpenGLFramebufferObjectFormat resolveFormat;
    resolveFormat.setInternalTextureFormat(GL_RGBA8);
    buffFormat.setSamples(0);

    m_resolveBuffer = new QOpenGLFramebufferObject(m_eyeWidth*2, m_eyeHeight, resolveFormat);

    // turn on compositor
    if (!vr::VRCompositor())
    {
        std::cerr << "Compositor initialization failed:" << std::endl;
        return;
    }

}


void GLWidget::updatePoses()
{
    vr::VRCompositor()->WaitGetPoses(m_trackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);

    for (unsigned int i=0; i<vr::k_unMaxTrackedDeviceCount; i++)
    {
        if (m_trackedDevicePose[i].bPoseIsValid)
        {
            m_matrixDevicePose[i] =  vrMatrixToQt(m_trackedDevicePose[i].mDeviceToAbsoluteTracking);
        }
    }

    if (m_trackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid)
    {
        m_hmdPose = glm::inverse(m_matrixDevicePose[vr::k_unTrackedDeviceIndex_Hmd]); //glm::translate(m_matrixDevicePose[vr::k_unTrackedDeviceIndex_Hmd], glm::vec3(0.f, 0.f, -1.7f));
    }
}

void GLWidget::updateInput()
{
    vr::VREvent_t event;
    while(m_hmd->PollNextEvent(&event, sizeof(event)))
    {
        //ProcessVREvent( event );
    }

    for(vr::TrackedDeviceIndex_t i=0; i<vr::k_unMaxTrackedDeviceCount; i++ )
    {
        vr::VRControllerState_t state;
        if(m_hmd->GetControllerState(i, &state, sizeof(state)))
        {
            if (state.ulButtonPressed & vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad))
            {
            }


            if (state.ulButtonPressed & vr::ButtonMaskFromId(vr::k_EButton_Grip))
            {
            }
        }
    }

}

glm::mat4x4 GLWidget::vrMatrixToQt(const vr::HmdMatrix34_t &mat)
{
    return glm::mat4x4(
        mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[0][3],
        mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[1][3],
        mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[2][3],
        0.0,         0.0,         0.0,         1.0f
    );
}

glm::mat4x4 GLWidget::vrMatrixToQt(const vr::HmdMatrix44_t &mat)
{
    return glm::mat4x4(
        mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[0][3],
        mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[1][3],
        mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[2][3],
        mat.m[3][0], mat.m[3][1], mat.m[3][2], mat.m[3][3]
    );
}

glm::mat4x4 GLWidget::viewProjection(vr::Hmd_Eye eye)
{
    glm::mat4x4 s;
    if (eye == vr::Eye_Left)
    {
        glm::mat4x4 viewProjection = glm::transpose(m_hmdPose * m_leftPose);
        return glm::translate(viewProjection, m_location);
    }
        //return m_hmdPose * m_leftPose; //glm::translate(m_leftPose * m_hmdPose * s, glm::vec3(10.f, 10.f, 10.f));
    else
    {
        glm::mat4x4 viewProjection = glm::transpose(m_hmdPose * m_rightPose);
        return glm::translate(viewProjection, m_location);
    }
//        return  m_hmdPose * m_rightPose; //glm::translate(m_rightPose * m_hmdPose * s, glm::vec3(10.f, 10.f, 10.f));
}

glm::mat4x4 GLWidget::perspectiveProjection(vr::Hmd_Eye eye) {
    glm::mat4x4 s;
    if (eye == vr::Eye_Left)
        return m_leftProjection;
    else
        return m_rightProjection;
}

QString GLWidget::getTrackedDeviceString(vr::TrackedDeviceIndex_t device, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError *error)
{
    uint32_t len = m_hmd->GetStringTrackedDeviceProperty(device, prop, NULL, 0, error);
    if(len == 0)
        return "";

    char *buf = new char[len];
    m_hmd->GetStringTrackedDeviceProperty(device, prop, buf, len, error);

    QString result = QString::fromLocal8Bit(buf);
    delete [] buf;

    return result;
}
