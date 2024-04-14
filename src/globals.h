//
// Created by itssiem on 4/5/24.
//

#ifndef CG_OPENGL_GLOBALS_H
#define CG_OPENGL_GLOBALS_H

#include <GL/glew.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Light.h"
#include "player.h"

const int WIDTH = 2000, HEIGHT = 1000;

const glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        1.0f * WIDTH / HEIGHT, 0.1f,
        20000.0f);

inline glm::mat4 view;

const Light light {.position = glm::vec3(2.0, 4.0, 6.0)};

inline player player;

inline GLuint program_id;

inline GLuint uniform_mv;
inline GLuint uniform_proj;
inline GLuint uniform_light_pos;
inline GLuint uniform_material_ambient;
inline GLuint uniform_material_diffuse;
inline GLuint uniform_specular;
inline GLuint uniform_material_power;
#endif //CG_OPENGL_GLOBALS_H
