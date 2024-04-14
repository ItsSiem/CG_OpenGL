//
// Created by itssiem on 4/14/24.
//

#include "Pyramid.h"

Pyramid::Pyramid(glm::vec3 scale, glm::vec3 position) : GameObject(position, default_material) {
    Scale(scale);
    this->vertices = CreateVertices();
    this->normals = CreateNormals();
    this->uvs = CreateUVs();
}

std::vector<glm::vec3> Pyramid::CreateVertices() {
    glm::vec3 a = glm::vec3(-0.5, -0.5, -0.5);
    glm::vec3 b = glm::vec3(0.5, -0.5, -0.5);
    glm::vec3 c = glm::vec3(0.5, -0.5, 0.5);
    glm::vec3 d = glm::vec3(-0.5, -0.5, 0.5);
    glm::vec3 e = glm::vec3(0, 0.5, 0);

    return std::vector<glm::vec3> {
        // Bottom
        a, b, c,
        a, c, d,
        // Front
        a, b, e,
        // Right
        b, c, e,
        // Back
        c, d, e,
        // Left
        d, a, e
    };
}

std::vector<glm::vec3> Pyramid::CreateNormals() {
    return std::vector<glm::vec3> {
       // the amount of normals should match the amount of vertices
         // Bottom
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        // Front
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        // Right
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        // Back
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        // Left
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0)

    };
}

std::vector<glm::vec2> Pyramid::CreateUVs() {
    return std::vector<glm::vec2> {
        // Bottom
        glm::vec2(0, 0),
        glm::vec2(1, 0),
        glm::vec2(1, 1),
        glm::vec2(0, 1),
        // Front
        glm::vec2(0.5, 0.5),
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        // Right
        glm::vec2(0.5, 0.5),
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        // Back
        glm::vec2(0.5, 0.5),
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        // Left
        glm::vec2(0.5, 0.5),
        glm::vec2(0, 1),
        glm::vec2(1, 1)
    };
}
