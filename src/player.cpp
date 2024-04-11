//
// Created by itssiem on 4/10/24.
//

#include <glm/ext/matrix_transform.hpp>
#include "player.h"
#include "globals.h"
#include "utils.h"

player::player() {
    position = glm::vec3(0.0, walk_height, 0.0);
    heading = glm::vec3(0, 0, 1);
    drone_mode = false;
}

void player::Update(const char key) {
    processInput(key);
    view = viewMatrix();
}

glm::mat4 player::viewMatrix() const {
    return glm::lookAt(position, position + heading, glm::vec3(0, 1, 0));
}

void player::processInput(const char key) {
    if (key == 'v')
        toggleDrone();
    if(drone_mode)
        processDroneMovement(key);
    else
        processWalkMovement(key);
    processHeading(key);
}

void player::processWalkMovement(const char key) {
    glm::vec3 norm_heading = glm::normalize(heading);
    glm::vec3 movement_vector(0);
    float movement_step = 0.1f;
    if (key == 'w')
        movement_vector = glm::vec3(norm_heading.x, 0, norm_heading.z);
    if (key == 's')
        movement_vector = -glm::vec3(norm_heading.x, 0, norm_heading.z);
    if (key == 'a')
        movement_vector = glm::vec3(norm_heading.z, 0, -norm_heading.x);
    if (key == 'd')
        movement_vector = glm::vec3(-norm_heading.z, 0, norm_heading.x);
    if (glm::length(movement_vector) != 0)
        position += glm::normalize(movement_vector) * movement_step;
}

void player::processDroneMovement(const char key) {
    glm::vec3 norm_heading = glm::normalize(heading);
    glm::vec3 movement_vector(0);
    float movement_step = 0.1f;
    if (key == 'w')
        movement_vector = norm_heading;
    if (key == 's')
        movement_vector = -norm_heading;
    if (key == 'a')
        movement_vector = glm::vec3(norm_heading.z, norm_heading.y, -norm_heading.x);
    if (key == 'd')
        movement_vector = glm::vec3(-norm_heading.z, norm_heading.y, norm_heading.x);
    if (key == 'q')
        movement_vector = glm::vec3(0, 1, 0);
    if (key == 'e')
        movement_vector = glm::vec3(0, -1, 0);
    position += movement_vector * movement_step;
}

void player::processHeading(const char key) {
    glm::vec3 normalized_heading = glm::normalize(heading);
    float rotate_step = DegToRad(1);
    glm::mat4 rotation_matrix(1);
    if (key == 'i')
        rotation_matrix = glm::rotate(glm::mat4(1), -rotate_step, glm::vec3(1, 0, 0));
    if (key == 'k')
        rotation_matrix = glm::rotate(glm::mat4(1), rotate_step, glm::vec3(1, 0, 0));
    if (key == 'j')
        rotation_matrix = glm::rotate(glm::mat4(1), rotate_step, glm::vec3(0, 1, 0));
    if (key == 'l')
        rotation_matrix = glm::rotate(glm::mat4(1), -rotate_step, glm::vec3(0, 1, 0));
    heading = glm::vec3( rotation_matrix * glm::vec4(heading, 1));
}

void player::toggleDrone() {
    if (drone_mode) {
        position = walk_position;
        heading = walk_heading;
    } else {
        walk_position = position;
        walk_heading = heading;
        position = drone_position;
        heading = drone_heading;
    }
    drone_mode = !drone_mode;
}
