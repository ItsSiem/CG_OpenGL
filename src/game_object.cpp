//
// Created by itssiem on 4/5/24.
//

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "game_object.h"
#include "globals.h"
#include "objloader.h"
#include "texture.h"
#include "utils.h"

GameObject::GameObject(const glm::vec3 pos) {
    model_transformation = glm::mat4(1);
    position = pos;
    Translate(pos);
}

GameObject::GameObject(const char *obj_file, const glm::vec3 position, const glm::vec3 color) : GameObject(
        Material{.ambient_color = color, .diffuse_color = color, .specular_color = color, .specular_power = 50,
                .texture = loadBMP("textures/blank.bmp")},
        glm::mat4(1)) {
    loadOBJ(obj_file, vertices, uvs, normals);
    this->position = position;
    Translate(position);
}

GameObject::GameObject(Material material, glm::mat4 model_transformation) {
    this->material = material;
    this->model_transformation = model_transformation;
}

void GameObject::Render() {
    InitBuffers();
    mv = view * model_transformation;
    glBindTexture(GL_TEXTURE_2D, material.texture);
    glUniform3fv(uniform_material_ambient, 1, glm::value_ptr(material.ambient_color));
    glUniform3fv(uniform_material_diffuse, 1, glm::value_ptr(material.diffuse_color));
    glUniform3fv(uniform_specular, 1, glm::value_ptr(material.specular_color));
    glUniform1f(uniform_material_power, material.specular_power);
    glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

void GameObject::InitBuffers() {
    GLuint position_id;
    GLuint normal_id;
    GLuint uv_id;
    GLuint vbo_vertices;
    GLuint vbo_normals;
    GLuint vbo_uvs;

    uv_id = glGetAttribLocation(program_id, "uv");

    // Get vertex attributes
    position_id = glGetAttribLocation(program_id, "position");
    normal_id = glGetAttribLocation(program_id, "normal");


    // Stop bind to vao
    glBindVertexArray(0);


    // Allocate memory for vbo
    glGenBuffers(1, &vbo_vertices);
    glGenBuffers(1, &vbo_normals);
    glGenBuffers(1, &vbo_uvs);

    // Bind to vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind to vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind to vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Allocate memory for vao
    glGenVertexArrays(1, &vao);

    // Bind to vao
    glBindVertexArray(vao);

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

void GameObject::Transform(glm::mat4 transform) {
    model_transformation *= transform;
    mv = view * model_transformation;
}

void GameObject::Translate(glm::vec3 translate) {
    Transform(glm::translate(glm::mat4(1), translate));
}

void GameObject::Rotate(float angle, glm::vec3 axis) {
    Transform(glm::rotate(glm::mat4(1), DegToRad(angle), axis));
}

void GameObject::Scale(float sx, float sy, float sz) {
    Transform(glm::scale(glm::mat4(1), glm::vec3(sx, sy, sz)));
}
