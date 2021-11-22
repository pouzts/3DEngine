#include <glad\glad.h>
#include <sdl.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Engine.h"
#include <iostream>

// vertices
const float vertices[] =
{
    // front
    -1.0f, -1.0f,  1.0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
     1.0f, -1.0f,  1.0, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     1.0f,  1.0f,  1.0, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f,  1.0, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    // back
    -1.0f, -1.0f, -1.0, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
     1.0f, -1.0f, -1.0, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
     1.0f,  1.0f, -1.0, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -1.0f,  1.0f, -1.0, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f
};

const GLuint indices[] =
{
    // front
    0, 1, 2,
    2, 3, 0,
    // right
    1, 5, 6,
    6, 2, 1,
    // back
    7, 6, 5,
    5, 4, 7,
    // left
    4, 0, 3,
    3, 7, 4,
    // bottom
    4, 5, 1,
    1, 0, 4,
    // top
    3, 2, 6,
    6, 7, 3
};

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

    std::shared_ptr<PhoenixEngine::VertexIndexBuffer> vertexBuffer = engine.Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::VertexIndexBuffer>("vertex_index_buffer");
    vertexBuffer->CreateVertexBuffer(sizeof(vertices), 8, (void*)vertices);
    vertexBuffer->CreateIndexBuffer(GL_UNSIGNED_INT, 36, (void*)indices);
    vertexBuffer->SetAttribute(0, 3, 8 * sizeof(GLfloat), 0); // position
    vertexBuffer->SetAttribute(1, 3, 8 * sizeof(GLfloat), 3 * sizeof(GLfloat)); // color
    vertexBuffer->SetAttribute(2, 2, 8 * sizeof(GLfloat), 6 * sizeof(GLfloat)); // uv

    // texture
    PhoenixEngine::Texture texture;
    texture.CreateTexture("textures/llama.jpg");
    texture.Bind();

    // uniform
    float time = 0;
    program->SetUniform("scale", time);

    glm::vec3 tint{1.0f, 0.5f, 0.5f};
    program->SetUniform("tint", tint);

    glm::vec4 view{ 1 };
    //view = glm::lookAt(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{0, 1, 0});
    program->SetUniform("view", view);

    glm::vec3 translate{ 0.0f };
    float angle = 0;

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
        engine.Update();

        time += engine.time.deltaTime;
        program->SetUniform("scale", 1.0f);

        if (engine.Get<PhoenixEngine::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == PhoenixEngine::InputSystem::eKeyState::Held)
        {
            translate.x -= 1 * engine.time.deltaTime;
        }
        if (engine.Get<PhoenixEngine::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == PhoenixEngine::InputSystem::eKeyState::Held)
        {
            translate.x += 1 * engine.time.deltaTime;
        }
        if (engine.Get<PhoenixEngine::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == PhoenixEngine::InputSystem::eKeyState::Held)
        {
            translate.y += 1 * engine.time.deltaTime;
        }
        if (engine.Get<PhoenixEngine::InputSystem>()->GetKeyState(SDL_SCANCODE_S) == PhoenixEngine::InputSystem::eKeyState::Held)
        {
            translate.y -= 1 * engine.time.deltaTime;
        }

        angle += engine.time.deltaTime;

        glm::mat4 model{ 1.0f };
        model = glm::scale(model, glm::vec3{0.25f});
        model = glm::rotate(model, angle, glm::vec3{0, 1, 0});
        model = glm::translate(model, translate);
        program->SetUniform("model", model);

        engine.Get<PhoenixEngine::Renderer>()->BeginFrame();

        vertexBuffer->Draw();

        engine.Get<PhoenixEngine::Renderer>()->EndFrame();
    }

    return 0;
}