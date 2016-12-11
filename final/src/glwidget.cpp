#include "glwidget.h"

#include "cs123_lib/resourceloader.h"
#include "cs123_lib/errorchecker.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <iostream>
#include "settings.h"

#include "gl/textures/Texture2D.h"
#include "gl/shaders/ShaderAttribLocations.h"
#include "../shapes/Cap.h"
#include "../shapes/Cone.h"
#include "../shapes/Square.h"
#include "../shapes/Cylinder.h"
#include "../shapes/ModeratelyComplexShape.h"
#include "../shapes/Sphere.h"
#include "../shapes/OpenGLShape.h"
#include "../shapes/lsystemtree.h"


using namespace CS123::GL;

GLWidget::GLWidget(QGLFormat format, QWidget *parent)
    : QGLWidget(format, parent),
      m_width(width()), m_height(height()),
      m_phongProgram(0), m_deferredSecondProgram(0),
      m_quad(nullptr), m_tree(nullptr),
      m_defShadingFBO(nullptr),
      m_angleX(-0.5f), m_angleY(0.5f), m_zoom(4.f),
      m_texID(0)
{
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

    // Initialize sphere OpenGLShape.
    float pi = 3.1415926535;
    std::vector<branch> branches(0);
    vec3 scale = glm::vec3(0.7, 0.7, 0.7);
    branches.push_back({scale, 0, 0, 0.0});
    branches.push_back({scale, 1, 0, 1});
    branches.push_back({scale, 0, 0, 1});
    branches.push_back({scale, -1, 0, 2});
    std::map<char, lSystemRule> rulesDict = {};
    rulesDict['F'] = lSystemRule{pi/10, 0, 0.5, branches};
    m_tree = std::make_unique<LSystemTree>(rulesDict);

    m_quad = std::make_unique<Square>();

    // Initialize texture
    QImage image(":/images/bark_tex3.jpg");
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
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw();
}

void GLWidget::draw() {
    glUseProgram(m_phongProgram);
    m_defShadingFBO->bind();
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texID);

    glm::mat4x4 loc = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));

    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "view"),  1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "projection"),  1, GL_FALSE, glm::value_ptr(m_projection));
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"),  1, GL_FALSE, glm::value_ptr(loc));
    m_tree->draw();
    m_defShadingFBO->unbind();
    glBindTexture(GL_TEXTURE_2D, 0);

    glUseProgram(m_deferredSecondProgram);

    glUniform1i(glGetUniformLocation(m_deferredSecondProgram, "NormalAndDiffuse"), 0);
    glUniform1i(glGetUniformLocation(m_deferredSecondProgram, "PosAndSpec"), 1);
    glUniform1i(glGetUniformLocation(m_deferredSecondProgram, "Color"), 2);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    m_defShadingFBO->getColorAttachment(0).bind();
    glActiveTexture(GL_TEXTURE1);
    m_defShadingFBO->getColorAttachment(1).bind();
    glActiveTexture(GL_TEXTURE2);
    m_defShadingFBO->getColorAttachment(2).bind();

    glUniformMatrix4fv(glGetUniformLocation(m_deferredSecondProgram, "view"),  1, GL_FALSE, glm::value_ptr(m_view));
    m_quad->draw();
    glUseProgram(0);
}

// This is called at the beginning of the program between initializeGL and
// the first paintGL call, as well as every time the window is resized.
void GLWidget::resizeGL(int w, int h) {
    m_width = w;
    m_height = h;

    // TODO: [Task 5] Initialize FBOs here, with dimensions m_width and m_height.
    m_defShadingFBO = std::make_unique<FBO>(3, FBO::DEPTH_STENCIL_ATTACHMENT::DEPTH_ONLY, m_width, m_height, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, TextureParameters::FILTER_METHOD::LINEAR);
    rebuildMatrices();
}

/// Mouse interaction code below.
void GLWidget::mousePressEvent(QMouseEvent *event) {
    m_prevMousePos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    m_angleX += 3.f * (event->x() - m_prevMousePos.x()) / (float) width();
    m_angleY += 3.f * (event->y() - m_prevMousePos.y()) / (float) height();
    m_prevMousePos = event->pos();
    rebuildMatrices();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
    m_zoom -= event->delta() / 100.f;
    rebuildMatrices();
}

void GLWidget::rebuildMatrices() {
    m_view = glm::translate(glm::vec3(0.f, -1.f, -m_zoom)) *
             glm::rotate(m_angleY, glm::vec3(1.f,0.f,0.f)) *
             glm::rotate(m_angleX, glm::vec3(0.f,1.f,0.f));

    m_projection = glm::perspective(0.8f, (float)width()/height(), 0.1f, 100.f);
    update();
}
