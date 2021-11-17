#pragma once
#include "Renderer.h"
#include "Resource/Resource.h"
#include "Math/MathTypes.h"
#include <SDL.h>
#include <glad/glad.h>

namespace PhoenixEngine
{
	class Texture : public Resource
	{
	public:
		~Texture();
		bool Load(const std::string& name, void* null) override;

		void Bind() { glBindTexture(target, texture); }
		bool CreateTexture(const std::string& filename, GLenum target = GL_TEXTURE_2D, GLuint unit = GL_TEXTURE0);

		static void FlipSurface(SDL_Surface* surface);

	protected:
		GLenum target{ GL_TEXTURE_2D };
		GLuint unit{ GL_TEXTURE0 };
		GLuint texture{ 0 };
	};
}