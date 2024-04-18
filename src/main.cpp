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
#include "Pyramid.h"

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

void Animate() {
    objects[6].Rotate(1, glm::vec3(0, 1, 0));
    objects[objects.size() - 1].Rotate(1, glm::vec3(0, 1, 0));
    objects[objects.size() - 1].Rotate(1, glm::vec3(1, 0, 0));

    objects[7].position += glm::vec3(0.01, 0, 0);
    objects[7].Translate(glm::vec3(0.01, 0, 0));
    if (objects[7].position.x > -4) {
        objects[7].position = glm::vec3(-6, 0, 1);
        objects[7].Translate(glm::vec3(-2, 0, 0));
    }

}

void Render(int n)
{
    player.Update();
    Render();
    Animate();
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
    Cube cube(glm::vec3(20, 0.0001, 20), glm::vec3(0, 0, 0));
    cube.material.texture = loadBMP("textures/uvtemplate.bmp");
    objects.push_back(cube);

    float revit_scale = 1 / 1000.0f;

    GameObject desk("objects/desk.obj", glm::vec3(-9.5, 0, -5.5), default_material);
    desk.material.texture = loadBMP("textures/wood.bmp");
    desk.Scale(revit_scale, revit_scale, revit_scale);
    desk.Rotate(-90, glm::vec3(1, 0, 0));
    desk.Rotate(90, glm::vec3(0, 0, 1));
    objects.push_back(desk);

    GameObject book_case("objects/book_case.obj", glm::vec3(0, 0, 0), default_material);
    book_case.material.texture = loadBMP("textures/blank.bmp");
    book_case.material.ambient_color = glm::vec3(61.0f / 255, 47.0f / 255, 22.0f / 255);
    book_case.Scale(revit_scale, revit_scale, revit_scale);
    book_case.Rotate(-90, glm::vec3(1, 0, 0));
    objects.push_back(book_case);

    GameObject coffee_table("objects/coffee_table.obj", glm::vec3(-5.5, 0, 0.8), default_material);
    coffee_table.material.texture = loadBMP("textures/blank.bmp");
    coffee_table.material.ambient_color = glm::vec3(61.0f / 255, 47.0f / 255, 22.0f / 255);
    coffee_table.Scale(revit_scale, revit_scale, revit_scale);
    coffee_table.Rotate(-90, glm::vec3(1, 0, 0));
    objects.push_back(coffee_table);

    GameObject coffee_table_2("objects/coffee_table.obj", glm::vec3(-6, 0, 1), default_material);
    coffee_table_2.material.texture = loadBMP("textures/blank.bmp");
    coffee_table_2.Scale(revit_scale, revit_scale, revit_scale);
    coffee_table_2.Rotate(-90, glm::vec3(1, 0, 0));
    objects.push_back(coffee_table_2);

    GameObject house("objects/house.obj", glm::vec3(0, 0, 0), default_material);
    house.material.texture = loadBMP("textures/blank.bmp");
    house.material.ambient_color = glm::vec3(41.0f / 255, 66.0f / 255, 117.0f / 255);
    house.Scale(revit_scale, revit_scale, revit_scale);
    house.Rotate(-90, glm::vec3(1, 0, 0));
    objects.push_back(house);

    GameObject teapot("objects/teapot.obj", coffee_table.position + glm::vec3(0, 0.43, 0), default_material);
    teapot.Scale(0.1, 0.1, 0.1);
    Material shiny = {
            .ambient_color = glm::vec3(0.1, 0.0, 0.0),
            .diffuse_color = glm::vec3(0.2, 0.0, 0.0),
            .specular_color = glm::vec3(0.1, 0.1, 0.1),
            .specular_power = 1024,
            .texture = loadBMP("textures/blank.bmp")
    };
    teapot.material = shiny;
    objects.push_back(teapot);

    Pyramid pyramid(glm::vec3(0.5, 0.5, 0.5), glm::vec3(-6, 0.5, 0));
    pyramid.material.texture = loadBMP("textures/blank.bmp");
    pyramid.material.ambient_color = glm::vec3(31.0f / 255, 61.0f / 255, 22.0f / 255);
    objects.push_back(pyramid);

    GameObject sofa("objects/sofa.obj", glm::vec3(-8, 0, 2.7), default_material);
    sofa.material.texture = loadBMP("textures/blank.bmp");
    sofa.material.ambient_color = glm::vec3(0.2, 0.2, 0.0);
    sofa.Scale(revit_scale, revit_scale, revit_scale);
    sofa.Rotate(-90, glm::vec3(1, 0, 0));
    objects.push_back(sofa);

    Cube leg1(glm::vec3(0.1, 1, 0.1), glm::vec3(-3, 0, 0.2));
    leg1.material.texture = loadBMP("textures/wood.bmp");
    objects.push_back(leg1);

    Cube leg2(glm::vec3(0.1, 1, 0.1), leg1.position + glm::vec3(0, 0, 0.6));
    leg2.material.texture = loadBMP("textures/wood.bmp");
    objects.push_back(leg2);

    Cube leg3(glm::vec3(0.1, 1, 0.1), leg1.position + glm::vec3(0.4, 0, 0));
    leg3.material.texture = loadBMP("textures/wood.bmp");
    objects.push_back(leg3);

    Cube leg4(glm::vec3(0.1, 1, 0.1), leg1.position + glm::vec3(0.4, 0, 0.6));
    leg4.material.texture = loadBMP("textures/wood.bmp");
    objects.push_back(leg4);

    Cube tabletop(glm::vec3(0.6, 0.05, 0.8), leg1.position + glm::vec3(0.2, 0.5, 0.3));
    tabletop.material.texture = loadBMP("textures/wood.bmp");
    objects.push_back(tabletop);

    GameObject torus("objects/torus.obj", coffee_table_2.position + glm::vec3(0, 0.55, 0), default_material);
    torus.Scale(0.1, 0.1, 0.1);
    torus.Rotate(90, glm::vec3(1, 0, 0));
    torus.material = shiny;
    torus.material.texture = loadBMP("textures/Yellobrk.bmp");
    objects.push_back(torus);
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
