#include "Engine.h"
#include <glad\glad.h>
#include <sdl.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
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

    // create scene
    std::unique_ptr<PhoenixEngine::Scene> scene = std::make_unique<PhoenixEngine::Scene>();
    scene->engine = &engine;

    PhoenixEngine::SeedRandom(static_cast<unsigned int>(time(nullptr)));
    PhoenixEngine::SetFilePath("../resources");

    std::shared_ptr<PhoenixEngine::Program> program = engine.Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Program>("basic_shader");
    std::shared_ptr<PhoenixEngine::Shader> vshader = engine.Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shader>("shaders/basic.vert", (void*)GL_VERTEX_SHADER);
    std::shared_ptr<PhoenixEngine::Shader> fshader = engine.Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shader>("shaders/basic.frag", (void*)GL_FRAGMENT_SHADER);

    program->AddShader(vshader);
    program->AddShader(fshader);
    program->Link();
    program->Use();

    // vertex buffer
    std::shared_ptr<PhoenixEngine::VertexIndexBuffer> vertexBuffer = engine.Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::VertexIndexBuffer>("cube_mesh");
    vertexBuffer->CreateVertexBuffer(sizeof(vertices), 8, (void*)vertices);
    vertexBuffer->CreateIndexBuffer(GL_UNSIGNED_INT, 36, (void*)indices);
    vertexBuffer->SetAttribute(0, 3, 8 * sizeof(GLfloat), 0); // position
    vertexBuffer->SetAttribute(1, 3, 8 * sizeof(GLfloat), 3 * sizeof(GLfloat)); // color
    vertexBuffer->SetAttribute(2, 2, 8 * sizeof(GLfloat), 6 * sizeof(GLfloat)); // uv

    // texture
    {
        auto texture = engine.Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Texture>("textures/llama.jpg");
        texture->Bind();

        texture = engine.Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Texture>("textures/wood.png");
        texture->Bind();

        /*texture = engine.Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Texture>("textures/rocks.bmp");
        texture->Bind();*/
    }

    // create camera
    {
        auto actor = PhoenixEngine::ObjectFactory::Instance().Create<PhoenixEngine::Actor>("Actor");
        actor->name = "camera";
        actor->transform.position = glm::vec3{ 0, 0, 10 };

        auto component = PhoenixEngine::ObjectFactory::Instance().Create<PhoenixEngine::CameraComponent>("CameraComponent");
        component->SetPerspective(45.0f, 800.0f / 600.0f, 0.01f, 100.0f);

        actor->AddComponent(std::move(component));
        scene->AddActor(std::move(actor));
    }

    // create cube
    {
        auto actor = PhoenixEngine::ObjectFactory::Instance().Create<PhoenixEngine::Actor>("Actor");
        actor->name = "cube";
        actor->transform.position = glm::vec3{ 0, 0, 0 };

        auto component = PhoenixEngine::ObjectFactory::Instance().Create<PhoenixEngine::MeshComponent>("MeshComponent");
        component->program = engine.Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Program>("basic_shader");
        component->vertexBuffer = engine.Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::VertexIndexBuffer>("cube_mesh");

        actor->AddComponent(std::move(component));
        scene->AddActor(std::move(actor));
    }

    // uniform
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

        scene->Update(engine.time.deltaTime);

        // update actor
        glm::vec3 direction{ 0 };
        if (engine.Get<PhoenixEngine::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == PhoenixEngine::InputSystem::eKeyState::Held) direction.x = -1;
        if (engine.Get<PhoenixEngine::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == PhoenixEngine::InputSystem::eKeyState::Held) direction.x = 1;
        if (engine.Get<PhoenixEngine::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == PhoenixEngine::InputSystem::eKeyState::Held) direction.z = -1;
        if (engine.Get<PhoenixEngine::InputSystem>()->GetKeyState(SDL_SCANCODE_S) == PhoenixEngine::InputSystem::eKeyState::Held) direction.z = 1;
        if (engine.Get<PhoenixEngine::InputSystem>()->GetKeyState(SDL_SCANCODE_E) == PhoenixEngine::InputSystem::eKeyState::Held) direction.y = 1;
        if (engine.Get<PhoenixEngine::InputSystem>()->GetKeyState(SDL_SCANCODE_Q) == PhoenixEngine::InputSystem::eKeyState::Held) direction.y = -1;

        auto actor = scene->FindActor("cube");
        if (actor != nullptr)
        {
            actor->transform.position += direction * 5.0f * engine.time.deltaTime;
            actor->transform.rotation.y += engine.time.deltaTime;
        }

        engine.Get<PhoenixEngine::Renderer>()->BeginFrame();

        scene->Draw(nullptr);

        engine.Get<PhoenixEngine::Renderer>()->EndFrame();
    }

    return 0;
}