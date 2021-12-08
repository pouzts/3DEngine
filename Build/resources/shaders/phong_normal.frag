#version 430 core

in VS_OUT
{
	vec3 position;
	vec3 light_position;
	vec2 texcoord;
} fs_in;

out vec4 outColor;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
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

layout(binding = 0) uniform sampler2D color_sample;
layout(binding = 1) uniform sampler2D normal_sample;

void main()
{
    // generate the normals from the normal map
    vec3 normal = texture(normal_sample, fs_in.texcoord).rgb;
    // convert rgb (0 <-> 1) to xyx (-1 <-> 1)
    normal = normalize(normal * 2.0 - 1.0);

    // ambient
	 vec3 ambient = material.ambient * light.ambient;
    
    // diffuse
    vec3 light_dir = normalize(vec3(fs_in.light_position) - fs_in.position);
    float intensity = max(dot(light_dir, normal), 0);
    vec3 diffuse = material.diffuse * light.diffuse * intensity;


    // specular
    vec3 specular = vec3(0);
    if (intensity > 0)
    {
        vec3 view_dir = normalize(-vec3(fs_in.position));
        vec3 reflection = reflect(-light_dir, normal);
        intensity = max(dot(view_dir, reflection), 0);
        intensity = pow(intensity, material.shininess);
        specular = material.specular * light.specular * intensity;
    }

    //fs_color = ambient + diffuse + specular;
	//outColor = texture(textureSampler, fs_texcoord) * vec4(fs_color, 1);
    outColor = vec4(ambient + diffuse, 1) * texture(color_sample, fs_in.texcoord) + vec4(specular, 1);
}