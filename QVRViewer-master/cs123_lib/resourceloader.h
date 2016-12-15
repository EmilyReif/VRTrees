#ifndef SHADER_H
#define SHADER_H

//#include "GL/glew.h"
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFramebufferObject>
#include <QOpenGLDebugMessage>
#include <QOpenGLDebugLogger>
#include <QOpenGLTexture>

class ResourceLoader {
public:
    ResourceLoader();
    static GLuint createShaderProgram(const char * vertex_file_path,const char * fragment_file_path, QOpenGLFunctions_4_1_Core *func);
    //static void initializeGlew();

private:
    static GLuint createShader(GLenum shaderType, const char *filepath, QOpenGLFunctions_4_1_Core *func);
};

#endif // SHADER_H
