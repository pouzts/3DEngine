#version 430 core 
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in vec3 tanget;

out VS_OUT
{
    vec3 position;
    vec2 texcoord;
    mat3 tbn;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    mat4 model_view = view * model;
    mat3 normal_matrix = transpose(inverse(mat3(model_view)));

    vs_out.position = vec3(model_view * vec4(position, 1));
    vs_out.texcoord = texcoord;

    vec3 N = normalize(normal_matrix * normal);
    vec3 T = normalize(normal_matrix * tanget);

    T = normalize(T - dot(T, N) * N);
   
    vec3 B = normalize(cross(N, T));

    vs_out.tbn = mat3(T, B, N);

    gl_Position = projection * view * model * vec4(position, 1.0);
}