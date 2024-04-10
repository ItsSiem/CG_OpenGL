//
// Created by itssiem on 4/10/24.
//

#ifndef CG_OPENGL_PLAYER_H
#define CG_OPENGL_PLAYER_H


#include <glm/vec3.hpp>
#include <glm/glm.hpp>

class player {
public:
    glm::vec3 position;
    glm::vec3 heading;
public:
    player();
    void Update(const char key = '\0');
private:
    glm::mat4 viewMatrix();
    void processInput(const char key);

};


#endif //CG_OPENGL_PLAYER_H
