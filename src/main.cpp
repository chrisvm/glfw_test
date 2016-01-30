#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <thread>
#include <cmath>
#include "shader.h"
#include "util.h"

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

// globals
GLuint program, vao;
int main() {
    // print header info
    fputs("Starting GLFW3 test\n", stdout);

    // init glfw, check if fail
    if (!glfwInit()) {
        Util::err_exit("Failed to init GLFW, exiting.\n", false);
    } else printf("Inited GLFW\n");

    // set error callback
    glfwSetErrorCallback(error_callback);

    // Set up OpenGL options.
    // Use OpenGL verion 3.3,
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
        Util::err_exit("Failed to create GLFW window.", true);
    }

    // use this window as the default context
    glfwMakeContextCurrent(window);

    // set keyboard callback
    glfwSetKeyCallback(window, key_callback);

    // init glew with all extensions
    glewExperimental = GL_TRUE;
    glewInit();
    printf("Inited GLEW\n");

    // print header
    Util::printHeader();

    // generate vertex arrays
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // create program
    program = glCreateProgram();

    // attach and create shaders
    GL::Shader vs = GL::Shader(GL_FRAGMENT_SHADER, "assets/shaders/fragment/standard.frag");
    GL::Shader fs = GL::Shader(GL_VERTEX_SHADER, "assets/shaders/vertex/standard.vert");
    vs.attachTo(program);
    fs.attachTo(program);
    printf("Shader compilation was successful\n");

    // link the program
    glLinkProgram(program);

    // load vertex data
    // composition: posx, posy, posz, rcolor, gcolor, bcolor, txcoordx, txcoordy
//    float vertices[] = { 0.25, -0.25, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0,
//                        -0.25, -0.25, 0.5, 0.0, 1.0, 0.0, 1.0, 0.0,
//                        -0.25,  0.25, 0.5, 0.0, 0.0, 1.0, 1.0, 1.0,
//                         0.25,  0.25, 0.5, 1.0, 1.0, 1.0, 0.0, 1.0 };
    float vertices[] = { 0.25, -0.25, 0.5, 1.0, 1.0, 1.0, 0.0, 0.0,
                         -0.25, -0.25, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0,
                         -0.25,  0.25, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0,
                         0.25,  0.25, 0.5, 1.0, 1.0, 1.0, 0.0, 1.0 };
    // create texture
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    // create the vertex and element buffers
    GLuint vbo, ebo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // create position's attrib pointer and buffer data to it's vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLint posAttrib = glGetAttribLocation(program, "position");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glEnableVertexAttribArray(posAttrib);

    GLint colorAttrib = glGetAttribLocation(program, "color");
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(colorAttrib);

    GLint texAttrib = glGetAttribLocation(program, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // create the elements
    GLuint elements[] = { 0, 1, 2,
                          0, 2, 3 };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    // use opengl program
    glUseProgram(program);

    // get texture and load to gpu
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    char const * textPath = "assets/images/normals/crystalite_color.jpg";
    Util::SOILImage* img = Util::loadImage(textPath);
    if (img == NULL) {
        printf("Error loading texture \"%s\"\n", textPath);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->image);
        glGenerateMipmap(GL_TEXTURE_2D);
        img->free();
    }

    // render loop
    auto t_start = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window)) {
        // get time
        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

        // Set up our black background color
        static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };

        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR, 0, black);

        // Draw our triangles
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}