#version 430 core

// Outputs
out vec4 vColor;

// Inputs
in vec4 position;
in vec4 color;

void main()
{
    gl_Position = position;

    vColor = color;
}