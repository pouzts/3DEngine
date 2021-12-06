#version 430 core 
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in vec3 tanget;

out VS_OUT
{
    vec3 position;
    vec3 normal;
    vec2 texcoord;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    mat4 model_view = view * model;
    mat3 normal_matrix = transpose(inverse(mat3(model_view)));

    vs_out.normal = normalize(normal_matrix * normal);
    vs_out.position = vec3(model_view * vec4(position, 1));
    vs_out.texcoord = texcoord;
   
    gl_Position = projection * view * model * vec4(position, 1.0);
}