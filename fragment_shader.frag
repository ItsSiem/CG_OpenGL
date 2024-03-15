#version 430 core

// Inputs from vertexshader
in vec3 vColor;
in VS_OUT{
    vec3 n;
    vec3 l;
    vec3 v;
} vs_in;

// Uniform inputs
uniform vec3 material_ambient;
uniform vec3 material_diffuse;
uniform vec3 material_specular_color;
uniform float material_specular_power;

// Output color
out vec4 fragColor;

void main()
{
    // Normalize incoming vectors
    vec3 N = normalize(vs_in.n);
    vec3 L = normalize(vs_in.l);
    vec3 V = normalize(vs_in.v);

    // Calculate R
     vec3 R = reflect(-L, N);

    // Calculate diffuse and specular components for frags
    vec3 diffuse = max(dot(N, L), 0.0) * material_diffuse;
    vec3 specular = pow(max(dot(R,V), 0.0), material_specular_power) * material_specular_color;

    // write final fragment to buffer
    fragColor = vec4(material_ambient + diffuse + specular, 1.0);
}
