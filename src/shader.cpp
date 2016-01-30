#include "shader.h"

namespace GL {
    // Public
    Shader::Shader(GLenum type, char const * location) {
        _handle = glCreateShader(type);

        GLchar* src = Util::fileToBuffer(location);
        glShaderSource(_handle, 1, (const GLchar**)&src, NULL);

        printf("Compiling Shader: %s ID: %i\n", location, _handle);
        glCompileShader(_handle);

        if (status() == GL_FALSE) {
            logError(location);
        }
    }

    GLuint Shader::getHandle() {
        return _handle;
    }

    GLint Shader::status() {
        GLint status;
        glGetShaderiv(_handle, GL_COMPILE_STATUS, &status);

        return status;
    }

    void Shader::attachTo(GLuint programId) {
        printf("Attaching shader: %i to program: %i\n", _handle, programId);
        glAttachShader(programId, _handle);
    }

    void Shader::detachFrom(GLuint programId) {
        printf("Detaching shader: %i from program: %i\n", _handle, programId);
        glDetachShader(programId, _handle);
        printf("Deleting shader: %i\n", _handle);
        glDeleteShader(_handle);
    }
    // END Public

    // Private
    void Shader::logError(char const * location) {
        GLint infoLogLength;
        glGetShaderiv(_handle, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(_handle, infoLogLength, NULL, strInfoLog);

        fprintf(stderr, "Shader Compile failure in %s:\n%s\n", location, strInfoLog);
        delete[] strInfoLog;
    }
    // END Private
}