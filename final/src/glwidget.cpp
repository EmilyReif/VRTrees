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
#include "forestmaker.h"

#include "terrain/terrain.h"
#include <chrono>


using namespace CS123::GL;

GLWidget::GLWidget(QGLFormat format, QWidget *parent)
    : QGLWidget(format, parent),
      m_width(width()), m_height(height()),
      m_phongProgram(0), m_deferredSecondProgram(0),
      m_quad(nullptr),
      m_forestMaker(nullptr),
      m_defShadingFBO(nullptr),
      m_angleX(-1.f), m_angleY(-0.1f), m_zoom(.5f),
      m_texNoiseID(0),
      m_startTime(std::chrono::steady_clock::now())
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

    m_quad = std::make_unique<Square>();
    m_forestMaker = std::make_unique<ForestMaker>();

    // Initialize textures.

    QImage imageNoise(":/images/noiseSmall.png");
    glGenTextures(1, &m_texNoiseID);
    glBindTexture(GL_TEXTURE_2D, m_texNoiseID);
    glTexImage2D(
         GL_TEXTURE_2D,
         0,
         GL_RGBA,
         imageNoise.width(),
         imageNoise.height(),
         0,
         GL_RGBA,
         GL_UNSIGNED_BYTE,
         imageNoise.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw();
    update();
}

void GLWidget::draw() {
    std::chrono::steady_clock::time_point currTime = std::chrono::steady_clock::now();

    std::chrono::milliseconds time_span = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - m_startTime);

    float currBranch = std::min(10., glm::floor(time_span.count()/3000.));
    float branchPercent = (time_span.count() % 3000) /3000.f;

    glUseProgram(m_phongProgram);
    m_defShadingFBO->bind();
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mat4x4 loc = translate(vec3(0.0f, 0.0f, 0.0f));

    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "view"),  1, GL_FALSE, value_ptr(m_view));
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "projection"),  1, GL_FALSE, value_ptr(m_projection));
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"),  1, GL_FALSE, value_ptr(loc));

    glActiveTexture(GL_TEXTURE0);
    glUniform1f(glGetUniformLocation(m_phongProgram, "currentBranch"), currBranch);
    glUniform1f(glGetUniformLocation(m_phongProgram, "percent"), branchPercent);
    std::vector<tree> trees = m_forestMaker->getTrees();
    {
        int numTrees = trees.size();
        for (int i = 0; i < numTrees; i++) {
            loc = trees[i].modelMatrix;
            glUniform1f(glGetUniformLocation(m_phongProgram, "colorID"),  trees[i].colorID);
            glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"),  1, GL_FALSE, value_ptr(loc));
            trees[i].treeShape->draw();
        }
        loc = glm::mat4x4();
        loc = glm::scale(loc, vec3(1, 0.5, 1));
        glUniform1f(glGetUniformLocation(m_phongProgram, "colorID"),  1);
        glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"),  1, GL_FALSE, value_ptr(loc));
        m_forestMaker->drawTerrain();
    }

    m_defShadingFBO->unbind();

    glUseProgram(m_deferredSecondProgram);
    glUniform1i(glGetUniformLocation(m_deferredSecondProgram, "NormalAndDiffuse"), 0);
    glUniform1i(glGetUniformLocation(m_deferredSecondProgram, "PosAndSpec"), 1);
    glUniform1i(glGetUniformLocation(m_deferredSecondProgram, "Noise"), 2);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    m_defShadingFBO->getColorAttachment(0).bind();
    glActiveTexture(GL_TEXTURE1);
    m_defShadingFBO->getColorAttachment(1).bind();
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_texNoiseID);


    glUniformMatrix4fv(glGetUniformLocation(m_deferredSecondProgram, "view"),  1, GL_FALSE, value_ptr(m_view));
    glUniformMatrix4fv(glGetUniformLocation(m_deferredSecondProgram, "projection"),  1, GL_FALSE, value_ptr(m_projection));
    m_quad->draw();
    glUseProgram(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}

// Just some quick helper functions to clean up the code.
float GLWidget::frandom(float low, float high) {
    return ((double)std::rand()/RAND_MAX)*(high - low) + low;
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
    m_angleX += 3.f * (event->x() - m_prevMousePos.x()) / (float) width();
    m_angleY += 3.f * (event->y() - m_prevMousePos.y()) / (float) height();
    m_prevMousePos = event->pos();
    rebuildMatrices();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
    m_zoom -= event->delta() / 600.f;
    rebuildMatrices();
}

void GLWidget::rebuildMatrices() {
    m_view = translate(vec3(0.f, 0.f, -m_zoom)) *
             rotate(m_angleY, vec3(1.f,0.f,0.f)) *
             rotate(m_angleX, vec3(0.f,1.f,0.f));

    m_projection = perspective(0.8f, (float)width()/height(), 0.1f, 100.f);
    update();
}
