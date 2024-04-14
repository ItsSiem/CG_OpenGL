//
// Created by itssiem on 4/14/24.
//

#include "Cube.h"

Cube::Cube(glm::vec3 scale, glm::vec3 position) : GameObject(position) {
    Scale(scale);
    vertices = CreateVertices();
    normals = CreateNormals();
    uvs = CreateUVs();
}

std::vector<glm::vec3> Cube::CreateVertices() {
    glm::vec3 a = glm::vec3(-0.5, 0.5, -0.5);
    glm::vec3 b = glm::vec3(0.5, 0.5, -0.5);
    glm::vec3 c = glm::vec3(-0.5, 0.5, 0.5);
    glm::vec3 d = glm::vec3(0.5, 0.5, 0.5);
    glm::vec3 e = glm::vec3(-0.5, -0.5, -0.5);
    glm::vec3 f = glm::vec3(0.5, -0.5, -0.5);
    glm::vec3 g = glm::vec3(-0.5, -0.5, 0.5);
    glm::vec3 h = glm::vec3(0.5, -0.5, 0.5);

    return std::vector<glm::vec3> {
        // Top
        a, b, c,
        b, d, c,
        // Bottom
        e, f, g,
        f, h, g,
        // Front
        e, f, a,
        f, b, a,
        // Back
        g, h, c,
        h, d, c,
        // Left
        e, g, a,
        g, c, a,
        // Right
        f, h, b,
        h, d, b
    };
}

std::vector<glm::vec3> Cube::CreateNormals() {
    return std::vector<glm::vec3> {
        // Top
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
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
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        // Back
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        // Left
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        // Right
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0)
    };
}

std::vector<glm::vec2> Cube::CreateUVs() {
    return std::vector<glm::vec2> {
        // Top
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(0, 0),
        glm::vec2(1, 1),
        glm::vec2(1, 0),
        glm::vec2(0, 0),
        // Bottom
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(0, 0),
        glm::vec2(1, 1),
        glm::vec2(1, 0),
        glm::vec2(0, 0),
        // Front
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(0, 0),
        glm::vec2(1, 1),
        glm::vec2(1, 0),
        glm::vec2(0, 0),
        // Back
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(0, 0),
        glm::vec2(1, 1),
        glm::vec2(1, 0),
        glm::vec2(0, 0),
        // Left
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(0, 0),
        glm::vec2(1, 1),
        glm::vec2(1, 0),
        glm::vec2(0, 0),
        // Right
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(0, 0),
        glm::vec2(1, 1),
        glm::vec2(1, 0),
        glm::vec2(0, 0)
    };
}

