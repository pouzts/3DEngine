#version 430 core 
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 fs_color;

uniform float scale;

void main()
{
    fs_color = color;
    gl_Position = vec4(position * scale, 1.0);
}