//
// Created by itssiem on 4/5/24.
//

#ifndef CG_OPENGL_MATERIAL_H
#define CG_OPENGL_MATERIAL_H

#include <glm/vec3.hpp>
#include <GL/glew.h>

struct Material
{
    glm::vec3 ambient_color;
    glm::vec3 diffuse_color;
    glm::vec3 specular_color;
    float specular_power;
    GLuint texture;
};

#endif //CG_OPENGL_MATERIAL_H
