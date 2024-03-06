#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glsl.h"

using namespace std;

GLuint program_id;

//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 800, HEIGHT = 600;


//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
    if (key == 27)
        glutExit();
}

// Init shaders
void InitShaders() {
    char* vertex_shader = glsl::readFile("vertex_shader.vert");
    char* fragment_shader = glsl::readFile("fragment_shader.frag");
    GLuint vsh_id = glsl::makeVertexShader(vertex_shader);
    GLuint fsh_id = glsl::makeFragmentShader(fragment_shader);
    program_id = glsl::makeShaderProgram(vsh_id, fsh_id);
}

//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
    glUseProgram(program_id);
    glPointSize(40.0f);
    glDrawArrays(GL_POINTS, 0, 1);
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


int main(int argc, char** argv)
{
    InitGlutGlew(argc, argv);

    // Main loop
    glutMainLoop();

    return 0;
}