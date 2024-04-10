#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "objloader.h"
#include "texture.h"
#include "game_object.h"
#include "globals.h"

using namespace std;

const char* fragshader_name = "fragment_shader.frag";
const char* vertexshader_name = "vertex_shader.vert";

unsigned const int DELTA_TIME = 10;

vector<GameObject> objects;

void keyboardHandler(unsigned char key, int a, int b)
{
    if (key == 27)
        glutExit();
}

void Render()
{
    // Define background
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Attach to program_id
    // Do transformations
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i].Render();
    }

    // Make uniform vars
    uniform_mv = glGetUniformLocation(program_id, "mv");
    uniform_proj = glGetUniformLocation(program_id, "projection");
    uniform_light_pos = glGetUniformLocation(program_id, "light_pos");
    uniform_material_ambient = glGetUniformLocation(program_id, "mat_ambient");
    uniform_material_diffuse = glGetUniformLocation(program_id, "mat_diffuse");
    uniform_specular = glGetUniformLocation(program_id, "mat_specular");
    uniform_material_power = glGetUniformLocation(program_id, "mat_power");


    // Attach to program (needed to fill uniform vars)
    glUseProgram(program_id);

    // Fill uniform vars
    glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3fv(uniform_light_pos, 1, glm::value_ptr(light.position));

    // Swap buffers
    glutSwapBuffers();
}

void Render(int n)
{
    Render();
    glutTimerFunc(DELTA_TIME, Render, 0);
}

void InitGlutGlew(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Hello OpenGL");
    glutDisplayFunc(Render);
    glutKeyboardFunc(keyboardHandler);
    glutTimerFunc(DELTA_TIME, Render, 0);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);

    glewInit();
}

void InitShaders()
{
    char* vertexshader = glsl::readFile(vertexshader_name);
    GLuint vsh_id = glsl::makeVertexShader(vertexshader);

    char* fragshader = glsl::readFile(fragshader_name);
    GLuint fsh_id = glsl::makeFragmentShader(fragshader);

    program_id = glsl::makeShaderProgram(vsh_id, fsh_id);
}

void CreateObjects() {
    GameObject cube;
    cube.material = Material {.ambient_color = glm::vec3(0, 0, 0), .diffuse_color = glm::vec3(0, 0, 0), .specular_color = glm::vec3(0, 0, 0), .specular_power = 50};
    cube.Rotate(45, glm::vec3(0, 1, 0));
    cube.Translate(glm::vec3(1, 0, 0));
    cube.Scale(3, 0.1, 3);
    loadOBJ("objects/box.obj", cube.vertices, cube.uvs, cube.normals);
    cube.material.texture = loadBMP("textures/blank.bmp");

    objects.push_back(cube);

    GameObject cube2("objects/box.obj", glm::vec3(0.3, 0.1, 0.2));
//    objects.push_back(cube2);
}

int main(int argc, char** argv)
{
    InitGlutGlew(argc, argv);
    InitShaders();
    CreateObjects();

    // Main loop
    glutMainLoop();

    return 0;
}
