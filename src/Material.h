//
// Created by itssiem on 4/5/24.
//

#ifndef CG_OPENGL_MATERIAL_H
#define CG_OPENGL_MATERIAL_H

#include <glm/vec3.hpp>
#include <GL/glew.h>
#include "texture.h"

struct Material
{
    glm::vec3 ambient_color;
    glm::vec3 diffuse_color;
    glm::vec3 specular_color;
    float specular_power;
    GLuint texture;
};

inline Material default_material = {
        .ambient_color = glm::vec3(0.5, 0.5, 0.5),
        .diffuse_color = glm::vec3(0.3, 0.3, 0.3),
        .specular_color = glm::vec3(0.7, 0.7, 0.7),
        .specular_power = 50,
        .texture = loadBMP("textures/uvtemplate.bmp"),
        };

#endif //CG_OPENGL_MATERIAL_H
