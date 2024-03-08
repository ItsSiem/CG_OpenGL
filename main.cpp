#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"

using namespace std;


//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 800, HEIGHT = 600;

const char* fragshader_name = "shaders/fragment_shader.frag";
const char* vertexshader_name = "shaders/vertex_shader.vert";


//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// ID's
GLuint program_id;
GLuint position_id;
GLuint color_id;

GLuint vbo_vertices;
GLuint vbo_colors;

const GLfloat vertices[] {
    0.5, -0.5, 0.0, 1.0,
    -0.5, -0.5, 0.0, 1.0,
    0.0, 0.5, 0.0, 1.0
};

const GLfloat colors[] {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
};

//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
    if (key == 27)
        glutExit();
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
    // Define background
    const glm::vec4 blue = glm::vec4(0.0f, 0.0f, 0.4f, 1.0f);
    glClearBufferfv(GL_COLOR, 0, glm::value_ptr(blue));

    // Attach to program_id
    glUseProgram(program_id);

    // Bind vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glVertexAttribPointer(position_id, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind colors
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glVertexAttribPointer(color_id, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(color_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Swap buffers
    glutSwapBuffers();
}


//------------------------------------------------------------
// void InitGlutGlew(int argc, char **argv)
// Initializes Glut and Glew
//------------------------------------------------------------

void InitGlutGlew(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Hello OpenGL");
    glutDisplayFunc(Render);
    glutKeyboardFunc(keyboardHandler);

    glewInit();
}


//------------------------------------------------------------
// void InitShaders()
// Initializes the fragmentshader and vertexshader
//------------------------------------------------------------

void InitShaders()
{
    char* vertexshader = glsl::readFile(vertexshader_name);
    GLuint vsh_id = glsl::makeVertexShader(vertexshader);

    char* fragshader = glsl::readFile(fragshader_name);
    GLuint fsh_id = glsl::makeFragmentShader(fragshader);

    program_id = glsl::makeShaderProgram(vsh_id, fsh_id);
}

void InitBuffers() {
    // vbo for vertices
    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vbo for colors
    glGenBuffers(1, &vbo_colors);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // get vertex attributes
    position_id = glGetAttribLocation(program_id, "position");
    color_id = glGetAttribLocation(program_id, "color");
}

int main(int argc, char** argv)
{
    InitGlutGlew(argc, argv);
    InitShaders();
    InitBuffers();

    // Main loop
    glutMainLoop();

    return 0;
}