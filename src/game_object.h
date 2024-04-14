//
// Created by itssiem on 4/5/24.
//

#ifndef CG_OPENGL_GAME_OBJECT_H
#define CG_OPENGL_GAME_OBJECT_H


#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include "Material.h"


class GameObject {
public:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    Material material;
    glm::mat4 model_transformation;
    glm::mat4 mv;
    glm::vec3 position;
private:
    GLuint vao;
public:
    GameObject(glm::vec3 pos);
    GameObject(const char* obj_file, const glm::vec3 position, const Material material);
    GameObject(const glm::vec3 position, const Material material);
    void InitBuffers();
    void Render();
    void Transform(glm::mat4);
    void Translate(glm::vec3);
    void Rotate(float angle, glm::vec3 axis);
    void Scale(glm::vec3 scale);
    void Scale(float sx, float sy, float sz);
};


#endif //CG_OPENGL_GAME_OBJECT_H
