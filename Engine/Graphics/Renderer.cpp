#include "Renderer.h"
#include "Math/MathUtils.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

namespace PhoenixEngine
{
	void Renderer::Startup()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		}

		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG );
		TTF_Init();
	}

	void Renderer::Shutdown()
	{
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
		
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
	}
	
	void Renderer::Update(float dt)
	{
	}
	
	void Renderer::Create(const std::string& name, int width, int height)
	{
		window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
		if (window == nullptr)
		{
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetSwapInterval(1);

		SDL_GLContext context = SDL_GL_CreateContext(window);
		if (!gladLoadGL())
		{
			SDL_Log("Failed to create OpenGL context");
			exit(-1);
		}
	}

	void Renderer::BeginFrame()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::EndFrame()
	{
		SDL_GL_SwapWindow(window);
	}
}
