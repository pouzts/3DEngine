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
    -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f
};

const GLuint indices[] =
{
    0, 2, 1,
    0, 3, 2
};

//// vertex shader
//const char* vertexSource = R"(
//    #version 430 core 
//    layout(location = 0) in vec3 position;
//    layout(location = 1) in vec3 color;
//
//    out vec3 fs_color;
//
//    uniform float scale;
//
//    void main()
//    {
//        fs_color = color;
//        gl_Position = vec4(position * scale, 1.0);
//    }
//)";
//
//// fragment
//const char* fragmentSource = R"(
//    #version 430 core
//
//    in vec3 fs_color;
//    out vec4 outColor;
//
//    uniform vec3 tint;
//
//    void main()
//    {
//        outColor = vec4(fs_color, 1.0) * vec4(tint, 1.0);
//    }
//)";

int main(int argc, char** argv)
{
    PhoenixEngine::Engine engine;
    engine.Startup();
    engine.Get<PhoenixEngine::Renderer>()->Create("OpenGL", 800, 600);

    PhoenixEngine::SeedRandom(static_cast<unsigned int>(time(nullptr)));
    PhoenixEngine::SetFilePath("../resources");

    std::shared_ptr<PhoenixEngine::Program> program = engine.Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Program>("basic_program");
    std::shared_ptr<PhoenixEngine::Shader> vshader = engine.Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shader>("shaders/basic.vert", (void*)GL_VERTEX_SHADER);
    std::shared_ptr<PhoenixEngine::Shader> fshader = engine.Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shader>("shaders/basic.frag", (void*)GL_FRAGMENT_SHADER);

    program->AddShader(vshader);
    program->AddShader(fshader);
    program->Link();
    program->Use();

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
    float time = 0;

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
        program->SetUniform("scale", std::sin(time));
        program->SetUniform("tint", tint);


        engine.Get<PhoenixEngine::Renderer>()->BeginFrame();

        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        engine.Get<PhoenixEngine::Renderer>()->EndFrame();
    }

    return 0;
}