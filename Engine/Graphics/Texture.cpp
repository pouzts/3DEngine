#include "Texture.h"
#include <SDL_image.h>

namespace PhoenixEngine
{
    Texture::~Texture()
    {
        glDeleteTextures(1, &texture);
    }

    bool Texture::Load(const std::string& name, void* data)
    {
        GLuint unit = static_cast<GLuint>(reinterpret_cast<std::uintptr_t>(data));
        return CreateTexture(name, GL_TEXTURE_2D, unit);
    }

    bool Texture::CreateTexture(const std::string& filename, GLenum target, GLuint unit)
    {
        this->target = target;
        this->unit = unit;

        SDL_Surface* surface = IMG_Load(filename.c_str());
        FlipSurface(surface);

        if (surface == nullptr)
        {
            SDL_Log("Failed to create surface: %s", SDL_GetError());
            return false;
        }

        glGenTextures(1, &texture);
        glBindTexture(target, texture);

        GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(target, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        /*glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP);*/
        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);

        return true;
    }

    void Texture::FlipSurface(SDL_Surface* surface)
    {
        SDL_LockSurface(surface);

        int pitch = surface->pitch; // row size
        uint8_t* temp = new uint8_t[pitch]; // intermediate buffer
        uint8_t* pixels = (uint8_t*)surface->pixels;

        for (int i = 0; i < surface->h / 2; ++i) {
            // get pointers to the two rows to swap
            uint8_t* row1 = pixels + i * pitch;
            uint8_t* row2 = pixels + (surface->h - i - 1) * pitch;

            // swap rows
            memcpy(temp, row1, pitch);
            memcpy(row1, row2, pitch);
            memcpy(row2, temp, pitch);
        }

        delete[] temp;

        SDL_UnlockSurface(surface);
    }
}