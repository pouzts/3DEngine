#version 430 core 
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

out vec3 fs_color;
out vec2 fs_texcoord;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Light
{
    vec4 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    mat4 model_view = view * model;

    // ambient
    vec3 ambient = material.ambient * light.ambient;
    
    // diffuse
    vec3 vnormal = mat3(model_view) * normal;
    vec4 vposition = model_view * vec4(position, 1);
    vec3 light_dir = normalize(vec3(light.position - vposition));

    float intensity = max(dot(light_dir, vnormal), 0);
    vec3 diffuse = material.diffuse * light.diffuse * intensity;

    // specular
    vec3 specular = vec3(0);
    if (intensity > 0)
    {
        vec3 view_dir = normalize(-vec3(vposition));
        vec3 reflection = reflect(-light_dir, vnormal);
        intensity = max(dot(view_dir, reflection), 0);
        intensity = pow(intensity, 64);
        specular = material.specular * light.specular * intensity;
    }

    fs_color = ambient + diffuse + specular;
    fs_texcoord = texcoord;
    gl_Position = projection * view * model * vec4(position, 1.0);
}