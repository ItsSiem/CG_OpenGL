#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "objloader.h"
#include "texture.h"

using namespace std;


//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 800, HEIGHT = 600;

const char* fragshader_name = "fragment_shader.frag";
const char* vertexshader_name = "vertex_shader.vert";

unsigned const int DELTA_TIME = 10;

unsigned const int NUM_OBJECTS = 3;


//--------------------------------------------------------------------------------
// Typedefs
//--------------------------------------------------------------------------------

struct LightSource
{
    glm::vec3 position;
};

struct Material
{
    glm::vec3 ambient_color;
    glm::vec3 diffuse_color;
    glm::vec3 specular_color;
    float power;
};


//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// ID's
GLuint program_id;
GLuint *vao = new GLuint[NUM_OBJECTS];
GLuint *texture_id = new GLuint[NUM_OBJECTS];

// Uniform ID's
GLuint uniform_mv;
GLuint uniform_proj;
GLuint uniform_light_pos;
GLuint uniform_material_ambient;
GLuint uniform_material_diffuse;
GLuint uniform_specular;
GLuint uniform_material_power;

// Matrices
glm::mat4 view(1), projection(1);
glm::mat4 *model = new glm::mat4[NUM_OBJECTS];
glm::mat4 *mv = new glm::mat4[NUM_OBJECTS];

// Material and light
LightSource light;
Material *material = new Material[NUM_OBJECTS];


//--------------------------------------------------------------------------------
// Mesh variables
//--------------------------------------------------------------------------------

vector<glm::vec3> *vertices = new vector<glm::vec3>[NUM_OBJECTS];
vector<glm::vec3> *normals = new vector<glm::vec3>[NUM_OBJECTS];
vector<glm::vec2> *uvs = new vector<glm::vec2>[NUM_OBJECTS];


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
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Attach to program_id
    glUseProgram(program_id);
    // Do transformations
    for (int i = 0; i < NUM_OBJECTS; i++)
    {
        model[i] = glm::rotate(model[i], 0.01f, glm::vec3(0.5f, 1.0f, 0.2f));
        mv[i] = view * model[i];
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glUniform3fv(uniform_material_ambient, 1, glm::value_ptr(material[i].ambient_color));
        glUniform3fv(uniform_material_diffuse, 1, glm::value_ptr(material[i].diffuse_color));
        glUniform3fv(uniform_specular, 1, glm::value_ptr(material[i].specular_color));
        glUniform1f(uniform_material_power, material[i].power);
        glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv[i]));
        
        glBindVertexArray(vao[i]);
        glDrawArrays(GL_TRIANGLES, 0, vertices[i].size());
        glBindVertexArray(0);
    }

    // Swap buffers
    glutSwapBuffers();
}


//------------------------------------------------------------
// void Render(int n)
// Render method that is called by the timer function
//------------------------------------------------------------

void Render(int n)
{
    Render();
    glutTimerFunc(DELTA_TIME, Render, 0);
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
    glutTimerFunc(DELTA_TIME, Render, 0);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);

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


//------------------------------------------------------------
// void InitMatrices()
//------------------------------------------------------------

void InitMatrices()
{
    model[2] = glm::translate(glm::mat4(1), glm::vec3(0.0, 0.0, 0.0));
    model[1] = glm::translate(glm::mat4(1), glm::vec3(-2.0, 0.0, 0.0));
    model[0] = glm::translate(glm::mat4(1), glm::vec3(2.0, 0.0, 0.0));
    
    view = glm::lookAt(
        glm::vec3(0.0, 2.0, 8.0),
        glm::vec3(0.0, 0.5, 0.0),
        glm::vec3(0.0, 1.0, 0.0));
    projection = glm::perspective(
        glm::radians(45.0f),
        1.0f * WIDTH / HEIGHT, 0.1f,
        20.0f);
    
    for (int i = 0; i < NUM_OBJECTS; i++)
        mv[i] = view * model[i];
}


//------------------------------------------------------------
// void InitObjects()
//------------------------------------------------------------

void InitObjects()
{
    // Objects
    int i = 0;
    loadOBJ("objects/teapot.obj", vertices[i], uvs[i], normals[i]);
    i++;
    loadOBJ("objects/torus.obj", vertices[i], uvs[i], normals[i]);
    i++;
    loadOBJ("objects/box.obj", vertices[i], uvs[i], normals[i]);
    texture_id[0] = loadBMP("textures/Yellobrk.bmp");
    texture_id[1] = loadBMP("textures/uvtemplate.bmp");
    texture_id[2] = loadBMP("textures/uvtemplate.bmp");
}


//------------------------------------------------------------
// void InitMaterialsLight()
//------------------------------------------------------------

void InitMaterialsLight()
{
    light.position = glm::vec3(4.0, 4.0, 4.0);
    for (int i = 0; i < NUM_OBJECTS; i++)
    {
        material[i].ambient_color = glm::vec3(0.2, 0.2, 0.1);
        material[i].diffuse_color = glm::vec3(0.5, 0.5, 0.3);
        material[i].specular_color = glm::vec3(0.5, 0.5, 0.5);
        material[i].power = 50.0;
    }
    // material.diffuse_color = glm::vec3(0.5, 0.0, 0.0);
}


//------------------------------------------------------------
// void InitBuffers()
// Allocates and fills buffers
//------------------------------------------------------------

void InitBuffers()
{
    GLuint position_id;
    GLuint normal_id;
    GLuint vbo_vertices;
    GLuint vbo_normals;
    GLuint vbo_uvs;


    GLuint uv_id = glGetAttribLocation(program_id, "uv");

    // Get vertex attributes
    position_id = glGetAttribLocation(program_id, "position");
    normal_id = glGetAttribLocation(program_id, "normal");


    // Stop bind to vao
    glBindVertexArray(0);

    for (int i = 0; i < NUM_OBJECTS; i++)
    {
        // Allocate memory for vbo
        glGenBuffers(1, &vbo_vertices);
        glGenBuffers(1, &vbo_normals);
        glGenBuffers(1, &vbo_uvs);

        // Bind to vbo
        glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
        glBufferData(GL_ARRAY_BUFFER, vertices[i].size() * sizeof(glm::vec3), &vertices[i][0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Bind to vbo
        glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
        glBufferData(GL_ARRAY_BUFFER, normals[i].size() * sizeof(glm::vec3), &normals[i][0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Bind to vbo
        glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
        glBufferData(GL_ARRAY_BUFFER, uvs[i].size() * sizeof(glm::vec2), &uvs[i][0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // Allocate memory for vao
        glGenVertexArrays(1, &vao[i]);

        // Bind to vao
        glBindVertexArray(vao[i]);

        // Bind vertices to vao
        glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
        glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(position_id);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Bind normals to vao
        glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
        glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(normal_id);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Bind uvs to vao
        glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
        glVertexAttribPointer(uv_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(uv_id);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
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
}


int main(int argc, char** argv)
{
    InitGlutGlew(argc, argv);
    InitShaders();
    InitMatrices();
    InitObjects();
    InitMaterialsLight();
    InitBuffers();

    // Main loop
    glutMainLoop();

    return 0;
}
