#version 430 core

// Uniform inputs
uniform mat4 mvp;

// Per-vertex inputs
in vec3 position;

// Outputs
out vec3 vColor;

void main()
{
    gl_Position = mvp * vec4(position, 1.0);

    vColor = vec3(1.0, 1.0, 1.0);
}
