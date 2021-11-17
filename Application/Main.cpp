#include <glad\glad.h>
#include <sdl.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Engine.h"
#include <iostream>

// vertices
const float vertices[] =
{
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f
};

const GLuint indices[] =
{
    0, 2, 1,
    0, 3, 2
};

// vertex shader
const char* vertexSource = R"(
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
)";

// fragment
const char* fragmentSource = R"(
    #version 430 core

    in vec3 fs_color;
    out vec4 outColor;

    uniform vec3 tint;

    void main()
    {
        outColor = vec4(fs_color, 1.0) * vec4(tint, 1.0);
    }
)";

int main(int argc, char** argv)
{
    PhoenixEngine::Engine engine;
    engine.Startup();
    engine.Get<PhoenixEngine::Renderer>()->Create("OpenGL", 800, 600);

    PhoenixEngine::SeedRandom(static_cast<unsigned int>(time(nullptr)));
    PhoenixEngine::SetFilePath("../resources");

    int result = SDL_Init(SDL_INIT_VIDEO);
    if (result != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

    // set vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        char buffer[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
        std::cout << buffer;
    }

    // set fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    //GLint fragStatus;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        char buffer[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
        std::cout << buffer;
    }

    // create shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // link and use program
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        char buffer[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, buffer);
        std::cout << buffer;
    }

    glUseProgram(shaderProgram);

    // vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // create vertex buffer
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint ebo; // Element buffer object
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLubyte*)NULL);
    glEnableVertexAttribArray(0);

    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // uniform
    GLuint location = glGetUniformLocation(shaderProgram, "scale");
    float time = 0;

    GLuint tintLocation = glGetUniformLocation(shaderProgram, "tint");
    glm::vec3 tint{1.0f, 0.5f, 0.5f};

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }

        SDL_PumpEvents();

        time += 0.01f;
        glUniform1f(location, std::sin(time));
        glUniform3fv(tintLocation, 1, &tint[0]);

        engine.Get<PhoenixEngine::Renderer>()->BeginFrame();

        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        engine.Get<PhoenixEngine::Renderer>()->EndFrame();
    }

    return 0;
}