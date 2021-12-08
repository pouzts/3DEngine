#version 430 core 
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in vec3 tanget;

out VS_OUT
{
	vec3 position;
    vec3 light_position;
	vec2 texcoord;
} vs_out;

struct Light
{
    vec4 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform Light light;

void main()
{
    mat4 model_view = view * model;
    mat3 normal_matrix = transpose(inverse(mat3(model_view)));

    vec3 N = normalize(normal_matrix * normal);
    vec3 T = normalize(normal_matrix * tanget);

    T = normalize(T - dot(T, N) * N);
   
    vec3 B = normalize(cross(N, T));

    mat3 tbn = transpose(mat3(T, B, N));

    vs_out.position = tbn * vec3(model_view * vec4(position, 1.0));
	vs_out.light_position = tbn * vec3(light.position);
	vs_out.texcoord = texcoord;

    gl_Position = projection * view * model * vec4(position, 1.0);
}