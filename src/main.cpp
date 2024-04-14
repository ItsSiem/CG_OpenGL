#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>

#include "glsl.h"
#include "objloader.h"
#include "texture.h"
#include "game_object.h"
#include "globals.h"
#include "Cube.h"

using namespace std;

const char* fragshader_name = "fragment_shader.frag";
const char* vertexshader_name = "vertex_shader.vert";

unsigned const int DELTA_TIME = 10;

vector<GameObject> objects;

void keyboardHandler(unsigned char key, int a, int b)
{
    if (key == 27)
        glutExit();
    player.Update(key);

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
    player.Update();
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
    GameObject ground("objects/box.obj", glm::vec3(0, 0, 0), default_material);
    ground.material.texture = loadBMP("textures/uvtemplate.bmp");
    ground.Scale(10, 0.0001, 10);
    objects.push_back(ground);

    Cube cube(glm::vec3(1, 1, 1), glm::vec3(0, 0, 0));
    cube.material.texture = loadBMP("textures/uvtemplate.bmp");
    objects.push_back(cube);

    float revit_scale = 1 / 1000.0f;

    GameObject desk("objects/desk.obj", glm::vec3(0, 0, -3), default_material);
    desk.material.texture = loadBMP("textures/uvtemplate.bmp");
    desk.Scale(revit_scale, revit_scale, revit_scale);
    desk.Rotate(-90, glm::vec3(1, 0, 0));
    objects.push_back(desk);

    GameObject coffee_table("objects/coffee_table.obj", glm::vec3(0, 0, 2), default_material);
    coffee_table.material.texture = loadBMP("textures/uvtemplate.bmp");
    coffee_table.Scale(revit_scale, revit_scale, revit_scale);
    coffee_table.Rotate(-90, glm::vec3(1, 0, 0));
    objects.push_back(coffee_table);

    GameObject teapot("objects/teapot.obj", coffee_table.position + glm::vec3(0, 0.43, 0), default_material);
    teapot.Scale(0.1, 0.1, 0.1);
    Material shiny = {
            .ambient_color = glm::vec3(0.0, 0.0, 0.0),
            .diffuse_color = glm::vec3(0.2, 0.2, 0.2),
            .specular_color = glm::vec3(0.7, 0.7, 0.7),
            .specular_power = 250,
            .texture = loadBMP("textures/Yellobrk.bmp")
    };
    teapot.material = shiny;
    objects.push_back(teapot);

    GameObject sofa("objects/sofa.obj", glm::vec3(3, 0, 0), default_material);
    sofa.material.texture = loadBMP("textures/uvtemplate.bmp");
    sofa.Scale(revit_scale, revit_scale, revit_scale);
    sofa.Rotate(-90, glm::vec3(1, 0, 0));
    objects.push_back(sofa);
}

void InitBuffers() {
    for (int i = 0; i < objects.size(); ++i) {
        objects[i].InitBuffers();
    }

}

int main(int argc, char** argv)
{
    InitGlutGlew(argc, argv);
    InitShaders();
    CreateObjects();
    InitBuffers();

    // Main loop
    glutMainLoop();

    return 0;
}
