//
// Created by itssiem on 4/10/24.
//

#ifndef CG_OPENGL_PLAYER_H
#define CG_OPENGL_PLAYER_H


#include <glm/vec3.hpp>
#include <glm/glm.hpp>

class player {
private:
    bool drone_mode;
    const float walk_height = 1.75;
    glm::vec3 walk_position = glm::vec3(-8, walk_height, 3);
    glm::vec3 walk_heading = glm::vec3(1, 0, -1);
    const glm::vec3 drone_position = glm::vec3(-9, 2.8, -3.5);
    const glm::vec3 drone_heading = glm::vec3(2, -1, 2);
public:
    glm::vec3 position;
    glm::vec3 heading;
public:
    player();
    void Update(const char key = '\0');
private:
    glm::mat4 viewMatrix() const;
    void processInput(const char key);
    void processWalkMovement(const char key);
    void processDroneMovement(const char key);
    void processHeading(const char key);
    void toggleDrone();
};


#endif //CG_OPENGL_PLAYER_H
