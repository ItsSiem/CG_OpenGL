//
// Created by itssiem on 4/14/24.
//

#ifndef CG_OPENGL_CUBE_H
#define CG_OPENGL_CUBE_H


#include "game_object.h"

class Cube : public GameObject {
public:
    Cube(glm::vec3 scale, glm::vec3 position);
private:
    std::vector<glm::vec3> CreateVertices();
    std::vector<glm::vec3> CreateNormals();
    std::vector<glm::vec2> CreateUVs();
};


#endif //CG_OPENGL_CUBE_H
