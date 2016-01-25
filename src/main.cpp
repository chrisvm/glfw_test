#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"

// The error callback will just print any errors that GLFW hits.
void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %u\n%s\n", error, description);
}

// The key callback generally handles any input, but we'll just use the ESC key in this example.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void err_exit(const char* desc, bool glfwDestroy) {
    fputs(desc, stderr);
    fputs("\n", stderr);
    if (glfwDestroy) {
        glfwTerminate();
    }
    exit(EXIT_FAILURE);
}

// globals
GLuint program, vao;
int main() {
    // print header info
    fputs("Starting GLFW3 test\n", stdout);

    // init glfw, check if fail
    if (!glfwInit()) {
        err_exit("Failed to init GLFW, exiting.\n", false);
    } else printf("Inited GLFW\n");

    // set error callback
    glfwSetErrorCallback(error_callback);

    // Set up OpenGL options.
    // Use OpenGL verion 4.1,
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    // GLFW_OPENGL_FORWARD_COMPAT specifies whether the OpenGL context should be forward-compatible,
    // i.e. one where all functionality deprecated in the requested version of OpenGL is removed.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // Indicate we only want the newest core profile, rather than using backwards compatible
    // and deprecated features.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Make the window resize-able.
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // create our window
    int wWidth = 800, wHeight = 600;
    GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, "GLFW Test", NULL, NULL);

    // window failed to be created
    if (!window) {
        // exit with error
        err_exit("Failed to create GLFW window.", true);
    }

    // use this window as the default context
    glfwMakeContextCurrent(window);

    // set keyboard callback
    glfwSetKeyCallback(window, key_callback);

    // init glew with all extensions
    glewExperimental = GL_TRUE;
    glewInit();
    printf("Inited GLEW\n");

    // print opengl version
    printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
    char resolved_path[256];
    realpath(".", resolved_path);
    printf("CWD: %s\n", resolved_path);
    // get shaders
    GL::Shader vs = GL::Shader(GL_FRAGMENT_SHADER, (char*)"assets/shaders/fragment/standard.frag");
    GL::Shader fs = GL::Shader(GL_VERTEX_SHADER, (char*)"assets/shaders/vertex/standard.vert");

    // create program
    program = glCreateProgram();

    // attach shaders
    vs.attachTo(program);
    fs.attachTo(program);

    // link the program
    glLinkProgram(program);

    // generate vertex arrays
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // use opengl program
    glUseProgram(program);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // Set up our green background color
        static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };

        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR, 0, green);

        // Draw our triangles
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}