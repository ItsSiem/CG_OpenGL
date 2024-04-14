//
// Created by itssiem on 4/14/24.
//

#ifndef CG_OPENGL_PYRAMID_H
#define CG_OPENGL_PYRAMID_H


#include "game_object.h"

class Pyramid : public GameObject {
public:
    Pyramid(glm::vec3 scale, glm::vec3 position);
private:
    std::vector<glm::vec3> CreateVertices();
    std::vector<glm::vec3> CreateNormals();
    std::vector<glm::vec2> CreateUVs();
};


#endif //CG_OPENGL_PYRAMID_H
