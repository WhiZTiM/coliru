#include "glfwSettings.h"
#include "Texture.h"

using namespace game;

int main()
{
    // So, it opens and context glfw in the best way
    GLFWwindow* window = openCorrectly(950, 550, "Sokobox II");

    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc (GL_ONE, GL_ONE);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Just for testing
    float vertices[] = {
    //  Position      Color             Texcoords
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
    };

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    char* vs = readFile("vertexShader");
    char* fs = readFile("fragmentShader");

    const GLchar* vertexSource = (const GLchar*) vs;
    const GLchar* fragmentSource = (const GLchar*) fs;

    // Shader sources
    /*const GLchar* vertexSource =
        "#version 150 core\n"
        "in vec2 position;"
        "void main() {"
        "   gl_Position = vec4(position, 0.0, 1.0);"
        "}";
    const GLchar* fragmentSource =
        "#version 150 core\n"
        "out vec4 outColor;"
        "void main() {"
        "   outColor = vec4(1.0, 1.0, 1.0, 1.0);"
        "}";*/

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);

    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

    if(status != GL_TRUE)
    {
        char buffer[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, buffer);

        delete[] vs;
        delete[] fs;

        throw std::runtime_error(buffer);
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
                           7*sizeof(float), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
                           7*sizeof(float), (void*)(2*sizeof(float)));

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
                           7*sizeof(float), (void*)(5*sizeof(float)));

    Texture monster("textures/monster.png");

    // And here's the game loop. Swapping buffers and polling events
    while(!glfwWindowShouldClose(window))
    {
        // Sets the window to should close if I press Esc
        // Therefore, this loop has to break
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Okay, do what it should do.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    delete[] vs;
    delete[] fs;

    // Bye bye!
    closeCorrectly();
    return 0;
}