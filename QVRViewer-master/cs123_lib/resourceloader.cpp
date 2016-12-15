#include "resourceloader.h"
#include <QFile>
#include <QTextStream>
#include <vector>


ResourceLoader::ResourceLoader()
{
}

GLuint ResourceLoader::createShaderProgram(const char *vertexFilePath,const char *fragmentFilePath, QOpenGLFunctions_4_1_Core *func) {
    // Create and compile the shaders.
    GLuint vertexShaderID = createShader(GL_VERTEX_SHADER, vertexFilePath, func);
    GLuint fragmentShaderID = createShader(GL_FRAGMENT_SHADER, fragmentFilePath, func);

    // Link the shader program.
    GLuint programId = func->glCreateProgram();
    func->glAttachShader(programId, vertexShaderID);
    func->glAttachShader(programId, fragmentShaderID);
    func->glLinkProgram(programId);

    // Print the info log.
    GLint result = GL_FALSE;
    int infoLogLength;
    func->glGetProgramiv(programId, GL_LINK_STATUS, &result);
    func->glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> infoLog(std::max(infoLogLength, int(1)));
        func->glGetProgramInfoLog(programId, infoLogLength, NULL, &infoLog[0]);
        fprintf(stdout, "%s\n", &infoLog[0]);
    }

    func->glDeleteShader(vertexShaderID);
    func->glDeleteShader(fragmentShaderID);

    return programId;
}

GLuint ResourceLoader::createShader(GLenum shaderType, const char *filepath, QOpenGLFunctions_4_1_Core *func) {
    GLuint shaderID = func->glCreateShader(shaderType);

    // Read shader file.
    std::string code;
    QString filepathStr = QString(filepath);
    QFile file(filepathStr);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        code = stream.readAll().toStdString();
    }

    // Compile shader code.
    printf("Compiling shader: %s\n", filepath);
    const char *codePtr = code.c_str();
    func->glShaderSource(shaderID, 1, &codePtr, NULL);
    func->glCompileShader(shaderID);

    // Print info log.
    GLint result = GL_FALSE;
    int infoLogLength;
    func->glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    func->glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> infoLog(infoLogLength);
        func->glGetShaderInfoLog(shaderID, infoLogLength, NULL, &infoLog[0]);
        fprintf(stdout, "%s\n", &infoLog[0]);
    }

    return shaderID;
}

//void ResourceLoader::initializeGlew() {
//    glewExperimental = GL_TRUE;
//    GLenum err = glewInit();
//    if (GLEW_OK != err) fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
//    fprintf(stdout, "Using GLEW %s\n", glewGetString(GLEW_VERSION));
//}
