#version 430 core

// Per-vertex inputs
in vec3 position;
in vec3 color;

// Outputs
out vec3 vColor;

void main()
{
    gl_Position = vec4(position, 1.0);

    vColor = color;
}