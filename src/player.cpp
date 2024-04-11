//
// Created by itssiem on 4/10/24.
//

#include <glm/ext/matrix_transform.hpp>
#include "player.h"
#include "globals.h"
#include "utils.h"

player::player() {
    position = glm::vec3(0.0, 2.0, 8.0);
    heading = glm::vec3(0.0, -1.5, -8.0);
}

void player::Update(const char key) {
    if(key != '\0')
        processInput(key);

    view = viewMatrix();
}

glm::mat4 player::viewMatrix() {
    return glm::lookAt(position, position + heading, glm::vec3(0, 1, 0));
}

void player::processInput(const char key) {
    glm::vec3 norm_heading = glm::normalize(heading);
    if (key == 'w')
        position += glm::vec3(norm_heading.x, 0, norm_heading.z);
    if (key == 's')
        position += -glm::vec3(norm_heading.x, 0, norm_heading.z);
    if (key == 'a')
        position += glm::vec3(norm_heading.z, 0, -norm_heading.x);
    if (key == 'd')
        position += glm::vec3(-norm_heading.z, 0, norm_heading.x);

    float rotate_step = DegToRad(1);
    glm::mat4 rotation_matrix(1);
    if (key == 'i') {
        rotation_matrix = glm::rotate(glm::mat4(1), -rotate_step, glm::vec3(1, 0, 0));
    }
    if (key == 'k') {
        rotation_matrix = glm::rotate(glm::mat4(1), rotate_step, glm::vec3(1, 0, 0));
    }
    if (key == 'j') {
        rotation_matrix = glm::rotate(glm::mat4(1), rotate_step, glm::vec3(0, 1, 0));
    }
    if (key == 'l') {
        rotation_matrix = glm::rotate(glm::mat4(1), -rotate_step, glm::vec3(0, 1, 0));
    }
    heading = glm::vec3( rotation_matrix * glm::vec4(heading, 1));
}
