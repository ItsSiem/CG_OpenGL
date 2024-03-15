#version 430 core

// Uniform inputs
uniform mat4 mv;
uniform mat4 projection;
uniform vec3 light_pos;
uniform vec3 material_ambient;
uniform vec3 material_diffuse;

// Per-vertex inputs
in vec3 position;
in vec3 normal;

// Outputs
out VS_OUT{
    vec3 n;
    vec3 l;
    vec3 v;
} vs_out;

void main()
{
    // calculate view-space
    vec4 p = mv * vec4(position, 1.0);

    // normal in view-space
    vs_out.n = mat3(mv) * normal;

    // light source in view-space
    vs_out.l = light_pos - p.xyz;

    //calc view vector
     vs_out.v = -p.xyz;

    gl_Position = projection * p;
}
