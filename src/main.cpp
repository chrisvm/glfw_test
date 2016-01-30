#include <stdio.h>
#include <cmath>
#include <thread>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "callbacks.h"

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
    glfwSetErrorCallback(Callbacks::error_callback);

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
    glfwSetKeyCallback(window, Callbacks::key_callback);

    // init glew with all extensions
    glewExperimental = GL_TRUE;
    glewInit();
    printf("Inited GLEW\n");

    // print header
    Util::printHeader();
    glEnable(GL_DEPTH_TEST);

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
    float vertices[] = {
             0.25, -0.25, 0.5, 1.0, 1.0, 1.0, 0.0, 0.0,
            -0.25, -0.25, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0,
            -0.25,  0.25, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0,
             0.25,  0.25, 0.5, 1.0, 1.0, 1.0, 0.0, 1.0,

             0.25, -0.25, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0,
            -0.25, -0.25, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0,
            -0.25,  0.25, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0,
             0.25,  0.25, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0,

    };
    // create texture
    GLuint tex;
    glActiveTexture(GL_TEXTURE0);
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
    GLuint elements[] = {
            0, 1, 2,
            0, 2, 3,

            0, 1, 4,
            1, 4, 5,

            3, 2, 7,
            2, 7, 6,

            1, 2, 6,
            1, 6, 5
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    // use opengl program
    glUseProgram(program);

    // get texture and load to gpu
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    char const * textPath = "assets/images/normals/crystalite_color.jpg";
    Util::SOILImage* img = Util::loadImage(textPath);
    if (img == NULL) {
        printf("Error loading texture \"%s\"\n", textPath);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->image);
        glGenerateMipmap(GL_TEXTURE_2D);
        img->free();
    }

    // get model transform uniform
    GLint uniModelTrans = glGetUniformLocation(program, "model");
    GLint uniViewTrans = glGetUniformLocation(program, "view");
    GLint uniProjTrans = glGetUniformLocation(program, "proj");

    // create matrix
    glm::mat4 modelTrans, viewTrans, projTrans;
    glm::vec3 cameraPos(1.2f, 1.2f, 1.2f);

    // 3d projection
    projTrans = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 1.0f, 10.0f);
    glUniformMatrix4fv(uniProjTrans, 1, GL_FALSE, glm::value_ptr(projTrans));

    // render loop
    auto t_start = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window)) {
        // get time
        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
        t_start = t_now;

        // rotate
        modelTrans = glm::rotate(
                modelTrans,
                glm::radians(45.0f) * time,
                glm::vec3(0.0f, 0.0f, 1.0f)
        );
        glUniformMatrix4fv(uniModelTrans, 1, GL_FALSE, glm::value_ptr(modelTrans));

        // check key presses
        if (Callbacks::getKey(GLFW_KEY_A)) {
            cameraPos.y += -0.1f;
        }
        if (Callbacks::getKey(GLFW_KEY_D)) {
            cameraPos.y +=  0.1f;
        }
        if (Callbacks::getKey(GLFW_KEY_W)) {
            cameraPos.x += -0.1f;
        }
        if (Callbacks::getKey(GLFW_KEY_S)) {
            cameraPos.x +=  0.1f;
        }

        // camera view
        viewTrans = glm::lookAt(
                cameraPos,
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 1.0f)
        );
        glUniformMatrix4fv(uniViewTrans, 1, GL_FALSE, glm::value_ptr(viewTrans));

        // Set up our black background color
        static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };

        // Clear the entire buffer with our green color (sets the background to be green).
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw our triangles
        glDrawElements(GL_TRIANGLES, sizeof(elements), GL_UNSIGNED_INT, 0);

        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}